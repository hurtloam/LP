/*
 * EventState.h
 *
 *  Created on: 9 dec. 2017
 *      Author: peter
 */

#ifndef INC_EVENTSTATE_H_
#define INC_EVENTSTATE_H_

class EventState {
public:
	EventState();
	virtual ~EventState();

	bool isBButton() const {
		return bButton;
	}

	void setBButton(bool button = false) {
		bButton = button;
	}

	bool isCButton() const {
		return cButton;
	}

	void setCButton(bool button = false) {
		cButton = button;
	}

	bool isCtrlButton() const {
		return ctrlButton;
	}

	void setCtrlButton(bool ctrlButton = false) {
		this->ctrlButton = ctrlButton;
	}

	bool isF10Button() const {
		return F10Button;
	}

	void setF10Button(bool f10Button = false) {
		F10Button = f10Button;
	}

	bool isF12Button() const {
		return F12Button;
	}

	void setF12Button(bool f12Button = false) {
		F12Button = f12Button;
	}

	bool isF8Button() const {
		return F8Button;
	}

	void setF8Button(bool f8Button = false) {
		F8Button = f8Button;
	}

	bool isF9Button() const {
		return F9Button;
	}

	void setF9Button(bool f9Button = false) {
		F9Button = f9Button;
	}

	bool isGButton() const {
		return gButton;
	}

	void setGButton(bool button = false) {
		gButton = button;
	}

	bool isIButton() const {
		return iButton;
	}

	void setIButton(bool button = false) {
		iButton = button;
	}

	bool isLeftButtonDown() const {
		return leftButtonDown;
	}

	void setLeftButtonDown(bool leftButtonDown = false) {
		this->leftButtonDown = leftButtonDown;
	}

	bool isLightDelete() const {
		return lightDelete;
	}

	void setLightDelete(bool lightDelete = false) {
		this->lightDelete = lightDelete;
	}

	bool isLightEnd() const {
		return lightEnd;
	}

	void setLightEnd(bool lightEnd = false) {
		this->lightEnd = lightEnd;
	}

	bool isLightHome() const {
		return lightHome;
	}

	void setLightHome(bool lightHome = false) {
		this->lightHome = lightHome;
	}

	bool isLightPageDown() const {
		return lightPageDown;
	}

	void setLightPageDown(bool lightPageDown = false) {
		this->lightPageDown = lightPageDown;
	}

	bool isShiftButton() const {
		return lShiftButton;
	}

	void setShiftButton(bool shiftButton = false) {
		lShiftButton = shiftButton;
	}

	bool isButton() const {
		return mButton;
	}

	void setButton(bool button = false) {
		mButton = button;
	}

	bool isMenuSelect() const {
		return menuSelect;
	}

	void setMenuSelect(bool menuSelect = false) {
		this->menuSelect = menuSelect;
	}

	bool isMiddleButtonDown() const {
		return middleButtonDown;
	}

	void setMiddleButtonDown(bool middleButtonDown = false) {
		this->middleButtonDown = middleButtonDown;
	}

	bool isMoveObj() const {
		return moveObj;
	}

	void setMoveObj(bool moveObj = false) {
		this->moveObj = moveObj;
	}

	bool isMoveObjDepth() const {
		return moveObjDepth;
	}

	void setMoveObjDepth(bool moveObjDepth = false) {
		this->moveObjDepth = moveObjDepth;
	}

	bool isMoveText() const {
		return moveText;
	}

	void setMoveText(bool moveText = false) {
		this->moveText = moveText;
	}

	bool isNButton() const {
		return nButton;
	}

	void setNButton(bool button = false) {
		nButton = button;
	}

	bool isPButton() const {
		return pButton;
	}

	void setPButton(bool button = false) {
		pButton = button;
	}

	bool isRButton() const {
		return rButton;
	}

	void setRButton(bool button = false) {
		rButton = button;
	}

	bool isRightButtonDown() const {
		return rightButtonDown;
	}

	void setRightButtonDown(bool rightButtonDown = false) {
		this->rightButtonDown = rightButtonDown;
	}

	bool isStartmY() const {
		return startmY;
	}

	void setStartmY(bool startmY = false) {
		this->startmY = startmY;
	}

	bool isTButton() const {
		return tButton;
	}

	void setTButton(bool button = false) {
		tButton = button;
	}

	bool isVButton() const {
		return vButton;
	}

	void setVButton(bool button = false) {
		vButton = button;
	}

	bool isXButton() const {
		return xButton;
	}

	void setXButton(bool button = false) {
		xButton = button;
	}

	bool isZButton() const {
		return zButton;
	}

	void setZButton(bool button = false) {
		zButton = button;
	}

  bool isRunning() const
  {
    return running;
  }

  void setRunning(bool running = false)
  {
    this->running = running;
  }

private:
	bool leftButtonDown = false;
	bool rightButtonDown = false;
	bool middleButtonDown = false;
	bool iButton = false;
	bool tButton = false;
	bool zButton = false;
	bool cButton = false;
	bool gButton = false;
	bool bButton = false;
	bool vButton = false;
	bool mButton = false;
	bool nButton = false;
	bool rButton = false;
	bool lShiftButton = false;
	bool pButton = false;
	bool xButton = false; // activate resource window
	bool F8Button = false; // activate resource window
	bool F9Button = false; // activate skybox stage making it possible to affect the skybox
	bool F10Button = false; // activate slower motion to camera
	bool F12Button = false; // activate first person movement via mouse (as m_button)
	bool ctrlButton = false; // move single step up or down

	bool moveText = false; // L Mouse button down we are moving the text
	bool moveObj = false;
	bool moveObjDepth = false;

	bool lightHome = false;
	bool lightEnd = false;
	bool lightDelete = false;
	bool lightPageDown = false;
	bool menuSelect = false;
	bool startmY = false;
  bool running = false;
};



#endif /* INC_EVENTSTATE_H_ */
