// Helper class; draws the world as seen by Bullet.
// This is very handy to see it Bullet's world matches yours.
// This example uses the old OpenGL API for simplicity,
// so you'll have to remplace GLFW_OPENGL_CORE_PROFILE by
// GLFW_OPENGL_COMPAT_PROFILE in glfwWindowHint()
// How to use this class :
// Declare an instance of the class :
// BulletDebugDrawer_DeprecatedOpenGL mydebugdrawer;
// dynamicsWorld->setDebugDrawer(&mydebugdrawer);
// Each frame, call it :
// mydebugdrawer.SetMatrices(ViewMatrix, ProjectionMatrix);
// dynamicsWorld->debugDrawWorld();

#include <GL/glew.h>
#include <LinearMath/btIDebugDraw.h>


class BulletDebugDrawer : public btIDebugDraw{
public:

	BulletDebugDrawer()
	:m_debugMode(0)
	{

	}

	void SetMatrices(glm::mat4 pViewMatrix, glm::mat4 pProjectionMatrix, GLuint programId){
    glUseProgram (programId); // Use Fixed-function pipeline (no shaders)
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(&pViewMatrix[0][0]);
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(&pProjectionMatrix[0][0]);
	}

	virtual void drawLine(const btVector3& from,const btVector3& to,const btVector3& color){
		std::vector<glm::vec3> tmp;
		tmp.push_back(glm::vec3(from.getX(),from.getY(), from.getZ()));
		tmp.push_back(glm::vec3(to.getX(),to.getY(), to.getZ()));

		glColor4f(color.getX(), color.getY(), color.getZ(), 1.0f);
//			glVertexPointer( 3,
//					GL_FLOAT,
//					0,
//					&tmp );
//
//			glPointSize( 5.0f );
//			glDrawArrays( GL_POINTS, 0, 2 );
//			glDrawArrays( GL_LINES, 0, 2 );
//		}
//		glPopMatrix();


			GLuint bufferId;
			glGenBuffers(1, &bufferId);
			glBindBuffer(GL_ARRAY_BUFFER, bufferId);
			glBufferData(GL_ARRAY_BUFFER, tmp.size() * sizeof(glm::vec3), &tmp[0], GL_STATIC_DRAW);

			// 1rst attribute buffer : vertices
			glBindBuffer(GL_ARRAY_BUFFER, bufferId);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(
					0,                  // attribute
					3,                  // size
					GL_FLOAT,           // type
					GL_FALSE,           // normalized?
					0,                  // stride
					(void*)0            // array buffer offset
			);

			glDrawArrays(GL_LINES, 0, tmp.size());
	}
	virtual void drawContactPoint(const btVector3 &,const btVector3 &,btScalar,int,const btVector3 &){}
	virtual void reportErrorWarning(const char *){}
	virtual void draw3dText(const btVector3 &,const char *){}
	virtual void setDebugMode(int debugMode){
		m_debugMode = debugMode;
	}
	int getDebugMode(void) const {return m_debugMode;}
	int m_debugMode;
};
