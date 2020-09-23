#ifndef DEF_BARADINHOLD_H
#define DEF_BARADINHOLD_H

#define MAX_ENCOUNTER 3

#define BHScriptName "instance_baradin_hold"

enum Creatures
{
    NPC_ARGALOTH            = 47120,
    NPC_OCCUTHAR            = 52363,
    NPC_ALIZABAL            = 55869,

	//Add
	NPC_FOCUSED_FIRE_DUMMY = 52369,
	NPC_OCCUTHAR_EYE = 52368,
	NPC_FEL_FIRESTORM_TRIGGER = 47829,
};

enum Gameobjects
{
	GO_ARGALOTH_DOOR = 207619,
	GO_OCCUTHAR_DOOR = 208953,
	GO_ALIZABAL_DOOR = 209849,
};

enum Data
{
    DATA_ARGALOTH   = 0,
    DATA_OCCUTHAR   = 1,
    DATA_ALIZABAL   = 2,   
	DATA_EYE_OF_OCCUTHAR,
	DATA_FOCUSED_FIRE_DUMMY,
};

#endif
