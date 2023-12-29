-- Configure Glycolysis

-- Use the createMolecule function in C

local c_glucose = 16000
local lp_glucose = c_glucose

local c_text_question = 80000

local c_molecule_spot = 61000
local lp_molecule_spot = c_molecule_spot
local c_text_spot = 62000

local lp_text_spot = c_text_question

local c_arrow = 26000
local lp_arrow = c_arrow
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

shape = {x=0.2, y=0.1, z=0.01}
scale = {x=1.0, y=1.0, z=1.0}

-- Glucose
id = lp_glucose + 1
--textureId = 1
pos = {x=0.1, y=21.0, z=0.1}
mInfo1 = "Glucose - A molecule in Glycolysis";
mInfo2 = "This was initiated from Lua";
mInfo3 = "This is LUA script writing this";
createMolecule(pos, id, objType["alpha_D_glucopyranose"], mInfo1, mInfo2, mInfo3)

--
lp_molecule_spot = lp_molecule_spot + 1
createMoleculeSpot(lp_molecule_spot, objType["molecule_spot"], shape, scale, pos)

-- Glucose6-phosphate
id = id + 1
pos = {x=0.1, y=19.5, z=0.1}
mInfo1 = "Glucose6-phosphate";
mInfo2 = "Lua version xxx was used ";
mInfo3 = "";
createMolecule(pos, id, objType["glucose6_phosphate"], mInfo1, mInfo2, mInfo3)

lp_molecule_spot = lp_molecule_spot + 1
createMoleculeSpot(lp_molecule_spot, objType["molecule_spot"], shape, scale, pos)

-- Fructose6-phosphate
id = id + 1
pos = {x=0.1, y=18.0, z=0.1}
mInfo1 = "Fructose6-phosphate";
mInfo2 = "It is a fructose sugar phosphorylated on carbon 6. The β-D-form of this compound is very common in cells.";
mInfo3 = "The vast majority of glucose and fructose entering a cell will become converted to this at some point. The name Neuberg ester comes from the German biochemist Carl Neuberg.";
createMolecule(pos, id, objType["fructose6_phosphate"], mInfo1, mInfo2, mInfo3)

lp_molecule_spot = lp_molecule_spot + 1
createMoleculeSpot(lp_molecule_spot, objType["molecule_spot"], shape, scale, pos)

-- Fructose1,6-bisphosphate
id = id + 1
pos = {x=0.1, y=16.5, z=0.1}
mInfo1 = "Fructose1,6-bisphosphate";
mInfo2 = "Also known as Harden-Young ester, is fructose sugar phosphorylated on\ncarbons 1 and 6. The β-";
mInfo3 = "D-form of this compound is very common in cells. The vast majority of\nglucose and fructose entering a cell will become converted to \nfructose 1,6-bisphosphate at some point.";
createMolecule(pos, id, objType["fructose1_6_bisphosphate"], mInfo1, mInfo2, mInfo3)

lp_molecule_spot = lp_molecule_spot + 1
createMoleculeSpot(lp_molecule_spot, objType["molecule_spot"], shape, scale, pos)

-- Dihydroxyacetone phosphate
id = id + 1
pos = {x=-1.0, y=15.8, z=0.1}
mInfo1 = "Dihydroxyacetone phosphate";
mInfo2 = "Dihydroxyacetone phosphate lies in the glycolysis metabolic pathway, and is one of the two products of breakdown of fructose 1,6-bisphosphate, along with glyceraldehyde 3-phosphate.";
mInfo3 = "It is rapidly and reversibly isomerised to glyceraldehyde 3-phosphate.";
createMolecule(pos, id, objType["dihydroxyacetone_phosphate"], mInfo1, mInfo2, mInfo3)

lp_molecule_spot = lp_molecule_spot + 1
createMoleculeSpot(lp_molecule_spot, objType["molecule_spot"], shape, scale, pos)

-- Glyceraldehyde 3-phosphate
id = id + 1
pos = {x=0.1, y=14.6, z=0.001}
mInfo1 = "Glyceraldehyde 3-phosphate";
mInfo2 = "";
mInfo3 = "";
createMolecule(pos, id, objType["glyceraldehyde_3_phosphate"], mInfo1, mInfo2, mInfo3)

lp_molecule_spot = lp_molecule_spot + 1
createMoleculeSpot(lp_molecule_spot, objType["molecule_spot"], shape, scale, pos)

-- 1,3-Bisphosphoglycerate
id = id + 1
pos = {x=0.1, y=12.9, z=0.001}
mInfo1 = "1,3-Bisphosphoglycerate";
mInfo2 = "";
mInfo3 = "";
createMolecule(pos, id, objType["one_three_bisphosphoglycerate"], mInfo1, mInfo2, mInfo3)

lp_molecule_spot = lp_molecule_spot + 1
createMoleculeSpot(lp_molecule_spot, objType["molecule_spot"], shape, scale, pos)

-- 3-Phosphoglycerate
id = id + 1
pos = {x=0.1, y=11.7, z=0.001}
mInfo1 = "3-Phosphoglycerate";
mInfo2 = "";
mInfo3 = "";
createMolecule(pos, id, objType["three_phosphoglycerate"], mInfo1, mInfo2, mInfo3)

lp_molecule_spot = lp_molecule_spot + 1
createMoleculeSpot(lp_molecule_spot, objType["molecule_spot"], shape, scale, pos)

-- 2-Phosphoglycerate
id = id + 1
pos = {x=0.1, y=10.5, z=0.001}
mInfo1 = "2-Phosphoglycerate";
mInfo2 = "";
mInfo3 = "";
createMolecule(pos, id, objType["two_phosphoglycerate"], mInfo1, mInfo2, mInfo3)

lp_molecule_spot = lp_molecule_spot + 1
createMoleculeSpot(lp_molecule_spot, objType["molecule_spot"], shape, scale, pos)

-- Phosphoenol pyruvate
id = id + 1
pos = {x=0.1, y=9.3, z=0.001}
mInfo1 = "Phosphoenol pyruvate";
mInfo2 = "";
mInfo3 = "";
createMolecule(pos, id, objType["phosphoenolpyruvate"], mInfo1, mInfo2, mInfo3)

lp_molecule_spot = lp_molecule_spot + 1
createMoleculeSpot(lp_molecule_spot, objType["molecule_spot"], shape, scale, pos)

-- Pyruvate
id = id + 1
pos = {x=0.1, y=8.1, z=0.001}
mInfo1 = "Pyruvate";
mInfo2 = "Pyruvic acid (CH3COCOOH) is the simplest of the alpha-keto acids, with a carboxylic acid and a ketone functional group.";
mInfo3 = "Pyruvate, the conjugate base, CH3COCOO−, is a key intermediate in several metabolic pathways.";
createMolecule(pos, id, objType["pyruvate"], mInfo1, mInfo2, mInfo3)

lp_molecule_spot = lp_molecule_spot + 1
createMoleculeSpot(lp_molecule_spot, objType["molecule_spot"], shape, scale, pos)

-- Arrows

id = lp_arrow + 1
scaling = {x=0.25, y=0.25, z=0.25}
pos = {x=0.02, y=20.3, z=0.0}
mInfo1 = "arrow_rectangle_down_single1";
mInfo2 = " ";
mInfo3 = " ";
createArrow(scaling, pos, id, objType["arrow_rectangle_down_single1"], 1, mInfo1, mInfo2, mInfo3);

id = lp_arrow + 2
scaling = {x=0.25, y=0.25, z=0.25}
pos = {x=0.0, y=18.7, z=0.0}
mInfo1 = "arrow_rectangle_down_up";
mInfo2 = " ";
mInfo3 = " ";
createArrow(scaling, pos, id, objType["arrow_rectangle_down_up"], 1, mInfo1, mInfo2, mInfo3);

id = lp_arrow + 3
scaling = {x=0.25, y=0.25, z=0.25}
pos = {x=0.0, y=17.3, z=0.0}
mInfo1 = "arrow_rectangle_down_single1";
mInfo2 = " ";
mInfo3 = " ";
createArrow(scaling, pos, id, objType["arrow_rectangle_down_single1"], 1, mInfo1, mInfo2, mInfo3);

id = lp_arrow + 4
scaling = {x=0.25, y=0.25, z=0.25}
pos = {x=0.0, y=15.7, z=0.0}
mInfo1 = "arrow_rectangle_down_side_long";
mInfo2 = " ";
mInfo3 = " ";
createArrow(scaling, pos, id, objType["arrow_rectangle_down_side_long"], 1, mInfo1, mInfo2, mInfo3);

id = lp_arrow + 5
scaling = {x=0.25, y=0.25, z=0.25}
pos = {x=-0.51, y=15.5, z=0.0}
mInfo1 = "arrow_rectangle_down_up_45_1";
mInfo2 = " ";
mInfo3 = " ";
createArrow(scaling, pos, id, objType["arrow_rectangle_down_up_45_1"], 1, mInfo1, mInfo2, mInfo3);

id = lp_arrow + 6
scaling = {x=0.25, y=0.25, z=0.25}
pos = {x=0.0, y=13.5, z=0.0}
mInfo1 = "arrow_rectangle_down_up_bent_long";
mInfo2 = " ";
mInfo3 = " ";
createArrow(scaling, pos, id, objType["arrow_rectangle_down_up_bent_long"], 1, mInfo1, mInfo2, mInfo3)

id = lp_arrow + 7
scaling = {x=0.25, y=0.25, z=0.25}
pos = {x=0.0, y=12.3, z=0.0}
mInfo1 = "arrow_rectangle_down_up_bent";
mInfo2 = " ";
mInfo3 = " ";
createArrow(scaling, pos, id, objType["arrow_rectangle_down_up_bent"], 1, mInfo1, mInfo2, mInfo3);

id = lp_arrow + 8
scaling = {x=0.25, y=0.25, z=0.25}
pos = {x=0.0, y=11.2, z=0.0}
mInfo1 = "arrow_rectangle_down_up";
mInfo2 = " ";
mInfo3 = " ";
createArrow(scaling, pos, id, objType["arrow_rectangle_down_up"], 1, mInfo1, mInfo2, mInfo3);

id = lp_arrow + 9
scaling = {x=0.25, y=0.25, z=0.25}
pos = {x=0.0, y=9.9, z=0.0}
mInfo1 = "arrow_rectangle_down_up_halfside_bent";
mInfo2 = " ";
mInfo3 = " ";
createArrow(scaling, pos, id, objType["arrow_rectangle_down_up_halfside_bent"], 1, mInfo1, mInfo2, mInfo3);

id = lp_arrow + 10
scaling = {x=0.25, y=0.25, z=0.25}
pos = {x=0.0, y=8.7, z=0.0}
mInfo1 = "arrow_rectangle_down_single1";
mInfo2 = " ";
mInfo3 = " ";
createArrow(scaling, pos, id, objType["arrow_rectangle_down_single1"], 1, mInfo1, mInfo2, mInfo3);


-- Adding Glucose-6-phosphate as an additional test for regulating the
-- amount of Hexokinase that will be available
-- Adding question text line
-- Regulation question

RegulatoryPos = {x=-3.5, y=-50.0, z=0.0}
createText(RegulatoryPos, c_text_question + 1, 1051)

-- HexokinaseQPos = {x=-4.5, y=22.0, z=0.0}
-- createText(HexokinaseQPos, c_text_question + 1, 1002)

-- Glucose-6-phosphate (down regulator) (regulates Hexokinase)
testPos = {x=-4.3, y=-50.0, z=0.0}
lp_text_spot = 62052
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)

RegulatoryPos = {x=-3.3, y=-50.0, z=0.0}
createText(RegulatoryPos, c_text_question + 2, 1056)


-- PhosphofructokinaseQPos = {x=-4.245, y=21.5, z=0.0}
-- createText(PhosphofructokinaseQPos, c_text_question + 2, 1007)

-- ATP (down regulator) (regulates Phosphofructokinase)
testPos = {x=-4.3, y=-50.0, z=0.0}
lp_text_spot = 62416
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)

-- Citrate (down regulator)
testPos = {x=-3.3, y=-50.0, z=0.0}
lp_text_spot = 62053
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)

-- AMP (up regulator)
testPos = {x=-2.3, y=-50.0, z=0.0}
lp_text_spot = 62055
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)


RegulatoryPos = {x=-4.3, y=-50.0, z=0.0}
createText(RegulatoryPos, c_text_question + 3, 1057)

-- PuruvateKinaseQPos = {x=-4.4, y=21.0, z=0.0}
-- createText(PuruvateKinaseQPos, c_text_question + 3, 1033)

-- ATP (down regulator) (regulates Phosphofructokinase)
testPos = {x=-4.25, y=-50.0, z=0.0}
lp_text_spot = 62516
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)

-- Alanin (down regulator)
testPos = {x=-3.25, y=-50.0, z=0.0}
lp_text_spot = 62054
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)

-- Fruktose 1,6.bisphosphate (up regulator)
testPos = {x=-2.25, y=-50.0, z=0.0}
lp_text_spot = 62008
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)


--  texture = 0 will set color usage in the ball objectg

id = lp_arrow + 11
scaling = {x=0.25, y=0.25, z=0.25}
pos = {x=-3.0, y=18.0, z=0.0}
-- texture = 0 will cause the ball object to use color
texture = 0 
createBall(id, pos, texture)

id = lp_arrow + 12
scaling = {x=0.25, y=0.25, z=0.25}
pos = {x=-3.0, y=17.0, z=0.0}
-- texture = 0 will cause the ball object to use color
texture = 0 
createBall(id, pos, texture)

id = lp_arrow + 13
scaling = {x=0.25, y=0.25, z=0.25}
pos = {x=-3.0, y=16.0, z=0.0}
-- texture = 0 will cause the ball object to use color
texture = 0 
createBall(id, pos, texture)





-----------------------------------------------------------------
-- End of Regulation Question
-----------------------------------------------------------------

-- Hexokinase
testPos = {x=-0.5, y=20.3, z=0.0}
lp_text_spot = 62002
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)

-- ATP
testPos = {x=0.5, y=20.51, z=0.0}
lp_text_spot = 62016
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)

-- ADP
testPos = {x=0.5, y=20.01, z=0.0}
lp_text_spot = 62017
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)

-- Phosphoglucose isomerase
testPos = {x=-0.5, y=18.7, z=0.0}
lp_text_spot = 62004
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)

-- Phosphofructokinase
testPos = {x=-0.5, y=17.2, z=0.0}
lp_text_spot = 62007
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)

-- ATP
testPos = {x=0.5, y=17.55, z=0.0}
lp_text_spot = 62116
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)

-- ADP
testPos = {x=0.5, y=17.05, z=0.0}
lp_text_spot = 62117
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)

-- Aldolase
testPos = {x=0.5, y=15.7, z=0.0}
lp_text_spot = 62009
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)

-- Triose phosphate isomerase
testPos = {x=-.8, y=15.2, z=0.0}
lp_text_spot = 62012
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)

-- Glyceraldehyde 3-phosphate dehydrogenase
testPos = {x=-0.5, y=13.45, z=0.0}
lp_text_spot = 62021
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)

-- Pi,NAD+
testPos = {x=0.5, y=13.8, z=0.0}
lp_text_spot = 62018
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)

-- NADH
testPos = {x=0.5, y=13.3, z=0.0}
lp_text_spot = 62019
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)

-- Phosphoglycerate kinase
testPos = {x=-0.5, y=12.2, z=0.0}
lp_text_spot = 62025
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)

-- ADP
testPos = {x=0.5, y=12.55, z=0.0}
lp_text_spot = 62217
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)

-- ATP
testPos = {x=0.5, y=12.05, z=0.0}
lp_text_spot = 62216
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)

-- Phosphoglycerate mutase
testPos = {x=-0.5, y=11.2, z=0.0}
lp_text_spot = 62028
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)

-- Enolase
testPos = {x=-0.5, y=9.9, z=0.0}
lp_text_spot = 62031
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)

-- H2O
testPos = {x=0.5, y=9.7, z=0.0}
lp_text_spot = 62020
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)


-- Pyruvate kinase
testPos = {x=-0.5, y=8.7, z=0.0}
lp_text_spot = 62033
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)


-- ADP
testPos = {x=0.5, y=8.95, z=0.0}
lp_text_spot = 62317
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)

-- ATP
testPos = {x=0.5, y=8.45, z=0.0}
lp_text_spot = 62316
createTextSpot(lp_text_spot, objType["text_spot"], shape, scale, testPos)



-- Animal Cell
--id = id + 1
--scaling = {x=2.5, y=2.5, z=2.5}
--pos = {x=-3.25, y=-170.0, z=-88.0}
--mInfo1 = "Animal Cell";
--mInfo2 = "Created from LUA script.";
--mInfo3 = " ";
--createAnimalCell(scaling, pos, id, mInfo1, mInfo2, mInfo3)