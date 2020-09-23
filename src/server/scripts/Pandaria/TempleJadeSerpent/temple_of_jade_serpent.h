/*
 * Trinity Core and update by WoWSource Forums
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Dungeon: Temple of the Jade Serpent.
 * Description: Header Script.
 */

#ifndef DEF_TEMPLE_OF_JADE_SERPENT_H_
#define DEF_TEMPLE_OF_JADE_SERPENT_H_

#include "SpellScript.h"
#include "Map.h"
#include "Creature.h"
#include "CreatureAIImpl.h"

#define MAX_ENCOUNTERS 4

enum DataTypes // Events / Encounters.
{
	DATA_WISE_MARI_EVENT             = 0,
	DATA_LOREWALKER_STONESTEP_EVENT  = 1,
	DATA_LIU_FLAMEHEART_EVENT        = 2,    
	DATA_SHA_OF_DOUBT_EVENT          = 3
};

enum Data     // GUID handling.
{
	DATA_WISE_MARI                   = 0,
	DATA_LOREWALKER_STONESTEP        = 1,
	DATA_LIU_FLAMEHEART              = 2,    
	DATA_SHA_OF_DOUBT                = 3,
    DATA_DOOR_WISE_MARI              = 4,
    DATA_DOOR_LOREWALKER_STONSTEP    = 5,
};

enum Bosses
{
    BOSS_WISE_MARI_DATA             = 0,
    BOSS_LOREWALKER_STONESTEP_DATA  = 1,
    BOSS_LIU_FLAMEHEART_DATA        = 2,
    BOSS_SHA_OF_DOUBT_DATA          = 3,

    MAX_ENCOUNTER = 4,
};

enum CreaturesIds
{
    // Bosses
    BOSS_WISE_MARI                   = 56448,
    BOSS_LOREWALKER_STONESTEP        = 56843,
    BOSS_LIU_FLAMEHEART              = 56732,
    BOSS_SHA_OF_DOUBT                = 56439,

    // NPCs
    NPC_BURST_TARGET                 = 34211,

    NPC_SCROLL                       = 57080,
    NPC_ZAO_SUNSEEKER                = 58826,
    NPC_SUN                          = 56915,
    NPC_SUN_TRIGGER                  = 56861,
    NPC_WISE_DRAGON                  = 59149,
    NPC_WELL                         = 56882,
    NPC_STRIFE_INI                   = 56871,
    NPC_HEROINE                      = 56873,
    NPC_MOON                         = 56874,
    NPC_SWIRLING_SUNFIRE             = 58815,
    NPC_JIANG                        = 59547,
    NPC_XIANG                        = 65317,

    NPC_STRIFE                       = 59051,
    NPC_PERIL                        = 59726,
    NPC_OSONG                        = 56872,

    NPC_MINION_OF_DOUBT              = 57109,
    NPC_LIU_FLAMEHEART               = 56732,
    NPC_YU_LON                       = 56762,
    NPC_JADE_FIRE                    = 56893,

    NPC_FIGMENT_OF_DOUBT             = 56792,
};

enum GameObjectIds
{
    GO_DOOR_WISE_MARI                = 213550,
    GO_DOOR_LOREWALKER_STONSTEP      = 213549,
    GO_DOOR_LIU_FLAMEHEART           = 213548,
    GO_DOOR_LIU_FLAMEHEART_2         = 213544
};

enum Action
{
    ACTION_SPAWN_SUNS                = 1,
    ACTION_SPAWN_STRIFE_AND_PERIL    = 2,
    ACTION_JUMP_START                = 3,
    ACTION_START_SHA_OF_DOUBT        = 4,
};

enum eSpell
{
    SPELL_PURIFIED_WATER = 118714,
};

#endif // DEF_TEMPLE_OF_JADE_SERPENT_H_
