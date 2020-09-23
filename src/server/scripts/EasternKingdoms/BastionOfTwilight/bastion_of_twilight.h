#ifndef DEF_BASTION_OF_TWILIGHT_H
#define DEF_BASTION_OF_TWILIGHT_H

#define BTScriptName "instance_bastion_of_twilight"

enum Data
{
    DATA_HALFUS                     = 0,
    DATA_VALIONA_THERALION          = 1,
    DATA_COUNCIL                    = 2,
    DATA_CHOGALL                    = 3,
    DATA_SINESTRA                   = 4,
    DATA_TEAM_IN_INSTANCE           = 5,
    DATA_VALIONA                    = 6,
    DATA_THERALION                  = 7,
    DATA_FELUDIUS                   = 8,
    DATA_IGNACIOUS                  = 9,
    DATA_ARION                      = 10,
    DATA_TERRASTRA                  = 11,
    DATA_MONSTROSITY                = 12,
    DATA_WHELP_CAGE                 = 13,
    DATA_HEALTH_VALIONA_THERALION   = 14,
    DATA_DLG_SINESTRA               = 15,
    DATA_DLG_HALFUS                 = 16,
    DATA_DLG_VALIONA_THERALION      = 17,
    DATA_DLG_CHOGALL                = 18,
    DATA_DLG_COUNCIL_1              = 19,
    DATA_DLG_COUNCIL_2              = 20,
    DATA_DLG_COUNCIL_3              = 21,
    DATA_DLG_ENTRANCE               = 22,
    DATA_WIPE_COUNT                 = 23,
};

enum CreatureIds
{
    NPC_HALFUS_WYRMBREAKER  = 44600,
    NPC_VALIONA             = 45992,
    NPC_THERALION           = 45993,
    NPC_FELUDIUS            = 43687,
    NPC_IGNACIOUS           = 43686,
    NPC_ARION               = 43688,
    NPC_TERRASTRA           = 43689,
	NPC_ELEMENTIUM_MONSTROSITY = 43735,
    NPC_CHOGALL             = 43324,
    NPC_SINESTRA            = 45213,
    NPC_CHOGALL_DLG         = 46965,  
	// Intro's and cutscenes - Misc
	NPC_CHOGALL_HALFUS = 46965,
	NPC_CHOGALL_DRAGONS = 48142,
	NPC_CHOGALL_COUNCIL = 46900
};

enum GameObjects
{
    GO_WHELP_CAGE           = 205087,
    GO_WHELP_CAGE2          = 205088,
    DOOR_HALFUS_ENTRANCE    = 205222,
    DOOR_HALFUS_EXIT        = 205223,
    DOOR_THER_ENTRANCE      = 205224,
    DOOR_THER_EXIT          = 205225,
    DOOR_COUNCIL_ENTRANCE   = 205226,
    DOOR_COUNCIL_EXIT       = 205227,
    DOOR_CHOGALL_ENTRANCE   = 205228,
    GO_CHOGALL_FLOOR        = 205898,
    GO_SINESTRA_DOOR        = 207679,
    GO_CACHE_OF_THE_BROODMOTHER = 208044, // loot chest of Sinestra
};

enum ActionsDlg
{
    ACTION_AT_ENTRANCE                  = 1, // 6341
    ACTION_AT_HALFUS_START              = 2, // 6437
    ACTION_AT_HALFUS_END                = 3, 
    ACTION_AT_VALIONA_THERALION_START   = 4, // 6442
    ACTION_AT_VALIONA_THERALION_END     = 5, 
    ACTION_AT_COUNCIL_1                 = 6, // 6625
    ACTION_AT_COUNCIL_2                 = 7, // 6626
    ACTION_AT_COUNCIL_3                 = 8, // 6627 
    ACTION_AT_CHOGALL                   = 9, // 6444
};

const Position randomPos[34] =
{
	{ -976.85f, -596.94f, 831.90f, 4.42f },
	{ -985.56f, -607.92f, 831.90f, 3.61f },
	{ -995.49f, -609.65f, 831.90f, 3.16f },
	{ -1010.19f, -616.54f, 831.90f, 3.66f },
	{ -1019.31f, -611.42f, 831.90f, 2.38f },
	{ -1033.72f, -610.70f, 834.02f, 3.02f },
	{ -1042.03f, -615.29f, 835.17f, 2.72f },
	{ -1047.88f, -605.81f, 835.20f, 1.91f },
	{ -1050.91f, -595.78f, 835.23f, 1.77f },
	{ -1052.30f, -578.92f, 835.02f, 1.53f },
	{ -1050.25f, -566.79f, 835.23f, 1.27f },
	{ -1043.81f, -554.45f, 835.20f, 0.87f },
	{ -1035.13f, -557.34f, 833.72f, 4.13f },
	{ -1041.10f, -571.14f, 833.11f, 4.33f },
	{ -1045.98f, -583.89f, 833.87f, 4.54f },
	{ -1036.06f, -589.51f, 831.90f, 0.65f },
	{ -1030.99f, -581.64f, 831.90f, 0.84f },
	{ -1021.70f, -571.16f, 831.90f, 0.84f },
	{ -1008.63f, -563.33f, 831.90f, 0.13f },
	{ -998.83f, -565.96f, 831.90f, 5.81f },
	{ -989.52f, -578.90f, 831.90f, 5.08f },
	{ -991.82f, -591.03f, 831.90f, 4.10f },
	{ -1000.78f, -590.82f, 831.90f, 2.38f },
	{ -1003.93f, -576.96f, 831.90f, 1.54f },
	{ -999.24f, -560.80f, 831.90f, 1.24f },
	{ -996.02f, -550.22f, 831.90f, 1.57f },
	{ -1003.03f, -538.78f, 831.90f, 2.67f },
	{ -999.54f, -530.48f, 831.89f, 0.09f },
	{ -986.53f, -540.11f, 831.90f, 5.88f },
	{ -975.28f, -547.22f, 831.90f, 5.59f },
	{ -970.45f, -558.16f, 831.90f, 5.06f },
	{ -964.18f, -570.52f, 831.90f, 5.95f },
	{ -963.99f, -583.44f, 831.90f, 4.39f },
	{ -976.46f, -585.91f, 831.90f, 2.92f }
};
const Position enterPos = {-548.15f, -532.34f, 890.60f, 0.0f};

#endif