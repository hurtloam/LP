-- Configure BioMolCraft

-- Use the loadStaticObjFile function in C

local c_glucose = 16000
local lp_glucose = c_glucose

-- Set arguments
objType = {
  cube = 0,
	creature0 = 1,
	creature1 = 2,
	creature2 = 3,
	creature3 = 4,
	creature4 = 5,
	creature5 = 6,
	creature6 = 7,
	creature7 = 8,
	creature8 = 9,
	creature9 = 10,
	creature10 = 11,
	creature11 = 12,
	creature12 = 13,
	creature13 = 14,
	creature14 = 15,
	creature15 = 16,
	creature16 = 17,
	creature17 = 18,
	creature18 = 19,
	creature19 = 20,
	creature20 = 21,
	creature21 = 22,
	creature22 = 23,
	creature23 = 24,
	boy = 25,
	landscape = 26,
	sniper1 = 27,
	sniper2 = 28,
	sniper3 = 29,
	sniper4 = 30,
	sniper5 = 31,
	sniper6 = 32,
	sniper7 = 33,
	sniper8 = 34,
	sniper9 = 35,
	sniper10 = 36,
	sniper11 = 37,
	sniper12 = 38,
	sniper13 = 39,
	sniper14 = 40,
	sniper15 = 41,
	sniper16 = 42,
	sniper17 = 43,
	sniper18 = 44,
	sniper19 = 45,
	sniper20 = 46,
	sniper21 = 47,
	sniper22 = 48,
	sniper23 = 49,
	sniper24 = 50,
	sniper25 = 51,
	sniper26 = 52,
	sniper27 = 53,
	sniper28 = 54,
	sniper29 = 55,
	pilot = 56,
	cylinder = 57,
	ball = 58,
	box = 59,
	glucose = 60,
	picture = 61,
	glyphs = 62,
	wall = 63,
	wall_2x32x32 = 64,
	plane = 65,
	arrow = 66,
	arrow2 = 67,
	mitochondria = 68,
	dna = 69,
	skybox = 70,
	ghost = 71,
	plate = 72,
	arrow3 = 73,
	arrow_rectangle_up_single = 74,
	arrow_rectangle_down_single = 75,
	arrow_rectangle_up_double = 76,
	arrow_rectangle_down_single1 = 77,
	arrow_rectangle_down_up = 78,
	arrow_rectangle_down_side = 79,
	arrow_rectangle_down_up_45 = 80,
	arrow_rectangle_down_up_45_1 = 81,
	arrow_rectangle_down_up_bent = 82,
	arrow_rectangle_down_side_long = 83,
	arrow_rectangle_down_up_bent_long = 84,
	arrow_rectangle_down_up_halfside_bent = 85,
	glucose6_phosphate = 86,
	hexokinase = 87,
	phosphofructokinase = 88,
	phospho_glycerate = 89,
	fructose6_phosphate = 90,
	fructose1_6_bisphosphate = 91,
	glyceraldehyde_3_phosphate = 92,
	alpha_D_glucopyranose = 93,
	dihydroxyacetone_phosphate = 94,
	one_three_bisphosphoglycerate = 95,
	three_phosphoglycerate = 96,
	two_phosphoglycerate = 97,
	phosphoenolpyruvate = 98,
	pyruvate = 99,
	atp = 100,
	animal_cell = 201,
  phosphoglucoseisomerase = 202,
  enolase = 203,
	line = 301,

	zombie = 101,
  maze_floor_3x1 = 102,
  maze_floor_3x5 = 103,
  maze_floor_3x10 = 104,
  maze_floor_3x3 = 105,
  maze_floor_5x5 = 106,
  maze_floor_3x20 = 107,
  maze_door_3x2 = 108,
  maze_door_x_3x3 = 109,
  maze_door_y_3x3 = 110,
  winning_area = 111,
  coordinate_lines = 112,
   molecule_spot = 113,
  text_spot = 114,
}

-- load resources other
loadStaticObjFiles("resources/obj/skybox/skybox.blend", objType["skybox"], "skybox", "");
loadStaticObjFiles("resources/obj/plate/plate_round_4x8.blend", objType["plate"], "plate", "");
loadStaticObjFiles("resources/obj/plane/plane4.blend", objType["plane"], "plane", "");
--loadStaticObjFiles("resources/obj/animal_cell/cell_animal.FBX", objType["animal_cell"], "animal cell", "animal_cell");

-- load resources molecules
loadStaticObjFiles("resources/obj/glucose6-phosphate/glucose6-phosphate_7.blend", objType["glucose6_phosphate"], "Glucose 6-phosphate", "Glucose_6-phosphate");
 loadStaticObjFiles("resources/obj/glucose/alpha_D_glucopyranose.obj", objType["alpha_D_glucopyranose"], "Glucose", "alpha_D_glucopyranose");
loadStaticObjFiles("resources/obj/fructose-6-phosphate/fructose-6-phosphate.obj", objType["fructose6_phosphate"], "Fructose 6-phosphate", "Fructose_6-phosphate");
loadStaticObjFiles("resources/obj/fructose1_6_bisphosphate/fructose1_6-bisphosphate.obj", objType["fructose1_6_bisphosphate"], "Fructose 1,6-bisphosphate", "Fructose_1,6-bisphosphate");
loadStaticObjFiles("resources/obj/glyceraldehyde_3_phosphate/glyceraldehyde_3_phosphate.obj", objType["glyceraldehyde_3_phosphate"], "glyceraldehyde_3_phosphate", "glyceraldehyde_3_phosphate");
loadStaticObjFiles("resources/obj/dihydroxyacetone_phosphate/dihydroxyacetone_phosphate.obj", objType["dihydroxyacetone_phosphate"], "dihydroxyacetone phosphate", "dihydroxyacetone_phosphate");
loadStaticObjFiles("resources/obj/1_3_bisphosphoglycerate/1_3_bisphosphoglycerate.obj", objType["one_three_bisphosphoglycerate"], "one_three_bisphosphoglycerate", "1,3-bisphosphoglycerate");
loadStaticObjFiles("resources/obj/3_phosphoglycerate/3_phosphoglycerate.obj", objType["three_phosphoglycerate"], "three_phosphoglycerate", "3-phosphoglycerate");
loadStaticObjFiles("resources/obj/2_phosphoglycerate/2_phosphoglycerate.obj", objType["two_phosphoglycerate"], "2 phosphoglycerate", "2-phosphoglycerate");
loadStaticObjFiles("resources/obj/phosphoenolpyruvate/phosphoenolpyruvate.obj", objType["phosphoenolpyruvate"], "phosphoenolpyruvate", "phosphoenolpyruvate");
loadStaticObjFiles("resources/obj/pyruvate/pyruvate.obj", objType["pyruvate"], "pyruvate", "pyruvate");

-- load resources arrows
loadStaticObjFiles ("resources/obj/arrow/arrow_rectangle_down_single_bent9.obj", objType["arrow_rectangle_down_single1"], "arrow_rectangle_down_single1", "");
loadStaticObjFiles ("resources/obj/arrow/arrow_rectangle_down_up_bent.obj",objType["arrow_rectangle_down_up_bent"], "arrow_rectangle_down_up_bent", "");
loadStaticObjFiles ("resources/obj/arrow/arrow_rectangle_down_up_halfside_bent.obj", objType["arrow_rectangle_down_up_halfside_bent"], "arrow_rectangle_down_up_halfside_bent", "");
loadStaticObjFiles ("resources/obj/arrow/arrow_rectangle_down_up_bent_long.obj", objType["arrow_rectangle_down_up_bent_long"], "arrow_rectangle_down_up_bent_long", "");
loadStaticObjFiles ("resources/obj/arrow/arrow_rectangle_down_up2.obj", objType["arrow_rectangle_down_up"], "arrow_rectangle_down_up", "");
loadStaticObjFiles ("resources/obj/arrow/arrow_rectangle_down_side.obj", objType["arrow_rectangle_down_side"], "arrow_rectangle_down_side", "");
loadStaticObjFiles ("resources/obj/arrow/arrow_rectangle_down_side_long.obj", objType["arrow_rectangle_down_side_long"], "arrow_rectangle_down_side_long", "");
loadStaticObjFiles ("resources/obj/arrow/arrow_rectangle_down_up_45.obj", objType["arrow_rectangle_down_up_45"], "arrow_rectangle_down_up_45", "");
loadStaticObjFiles ("resources/obj/arrow/arrow_rectangle_down_up_45_1.obj", objType["arrow_rectangle_down_up_45_1"], "arrow_rectangle_down_up_45_1", "");
loadStaticObjFiles ("resources/obj/arrow/arrow_rectangle_up_single.blend", objType["arrow_rectangle_up_single"], "arrow_rectangle_up_single", "");
loadStaticObjFiles ("resources/obj/arrow/arrow_rectangle_up_double.blend", objType["arrow_rectangle_up_double"], "arrow_rectangle_up_double", "");

loadStaticObjFiles("resources/obj/landscape/landscape.obj", objType["landscape"], "landscape", "");
loadStaticObjFiles ("resources/obj/maze/maze_floor_3x3.blend", objType["maze_floor_3x3"], "maze_floor_3x3", "");

loadStaticObjFiles("resources/obj/box/blender_ball.obj",  objType["ball"], "ball", "ball");