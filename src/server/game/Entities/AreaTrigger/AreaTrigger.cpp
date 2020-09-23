/*
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
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
 */

#include "ObjectAccessor.h"
#include "GridNotifiersImpl.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "Unit.h"
#include "SpellInfo.h"
#include "Log.h"
#include "AreaTrigger.h"

AreaTrigger::AreaTrigger() : WorldObject(false), _duration(0), m_caster(NULL), m_visualRadius(0.0f)
{
    m_objectType |= TYPEMASK_AREATRIGGER;
    m_objectTypeId = TYPEID_AREATRIGGER;

    m_updateFlag = UPDATEFLAG_STATIONARY_POSITION;

    m_valuesCount = AREATRIGGER_END;
}

AreaTrigger::~AreaTrigger()
{
    ASSERT(!m_caster);
}

void AreaTrigger::AddToWorld()
{
    ///- Register the AreaTrigger for guid lookup and for caster
    if (!IsInWorld())
    {
        sObjectAccessor->AddObject(this);
        WorldObject::AddToWorld();
        BindToCaster();
    }
}

void AreaTrigger::RemoveFromWorld()
{
    ///- Remove the AreaTrigger from the accessor and from all lists of objects in world
    if (IsInWorld())
    {
        UnbindFromCaster();
        WorldObject::RemoveFromWorld();
        sObjectAccessor->RemoveObject(this);
    }
}

bool AreaTrigger::CreateAreaTrigger(uint32 guidlow, uint32 triggerEntry, Unit* caster, SpellInfo const* spell, Position const& pos)
{
    SetMap(caster->GetMap());
    Relocate(pos);
    if (!IsPositionValid())
    {
        sLog->outError(LOG_FILTER_GENERAL, "AreaTrigger (spell %u) not created. Invalid coordinates (X: %f Y: %f)", spell->Id, GetPositionX(), GetPositionY());
        return false;
    }

    WorldObject::_Create(guidlow, HIGHGUID_AREATRIGGER, caster->GetPhaseMask());

    SetEntry(triggerEntry);
    SetDuration(spell->GetDuration());
    SetObjectScale(1);

    SetUInt64Value(AREATRIGGER_CASTER, caster->GetGUID());
    SetUInt32Value(AREATRIGGER_SPELLID, spell->Id);
    SetUInt32Value(AREATRIGGER_SPELLVISUALID, spell->SpellVisual[0]);
    SetUInt32Value(AREATRIGGER_DURATION, spell->GetDuration());
    SetFloatValue(AREATRIGGER_FIELD_EXPLICIT_SCALE, GetObjectScale());

    switch (spell->Id)
    {
        case 116011: // Rune of Power.
            SetVisualRadius(3.5f);
            break;
        case 116235: // Amethyst Pool.
            SetVisualRadius(3.5f);
            break;
        case 102793: // Ursol's Vortex
        case 51052:
        case 62618:
            SetVisualRadius(8.0f);
            break;
        // Heart of Fear.

        case 123811: // Pheromones of Zeal Zor'lok.
            SetVisualRadius(100.0f);
            SetDuration(5000000);
            break;
        case 122731: // Noise Cancelling Zor'lok.
            SetVisualRadius(4.0f);
            break;

        // Siege of Orgrimmar.

        case 147181: // Rushing Waters - Swirl zone NE
        case 147178: // Rushing Waters - Swirl zone N
        case 147182: // Rushing Waters - Swirl zone NW
        case 147191: // Rushing Waters - Swirl zone SW
        case 147189: // Rushing Waters - Swirl zone SE
            SetVisualRadius(9.0f);
            SetDuration(500);
            break;

        case 143235: // Noxious Poison He Softfoot
            SetVisualRadius(3.5f);
            SetDuration(60000);
            break;
        case 143546: // Dark Meditation Sun Tenderheart
            SetVisualRadius(10.0f);
            SetDuration(600000);
            break;
        case 143960: // Defiled Ground Embodied Misery
            SetVisualRadius(4.0f);
            SetDuration(60000);
            break;

        case 146793: // Bottomless Pit Greater Corruption
            SetVisualRadius(4.0f);
            SetDuration(60000);
            break;

        default: break;
    }

    if (!GetMap()->AddToMap(this))
        return false;

    return true;
}

void AreaTrigger::Update(uint32 p_time)
{
    if (GetDuration() > int32(p_time))
        _duration -= p_time;
    else
        Remove(); // expired

    WorldObject::Update(p_time);

    // Handle all special AreaTriggers here.

    SpellInfo const* m_spellInfo = sSpellMgr->GetSpellInfo(GetUInt32Value(AREATRIGGER_SPELLID));
    if (!m_spellInfo)
        return;

    if (!GetCaster())
    {
        Remove();
        return;
    }

    Unit* caster = GetCaster();
    float radius = 0.0f;

    // Custom MoP Script
    switch (m_spellInfo->Id)
    {
        case 51052: // Anti-Magic Zone
        {
            UnitList targets;
            WoWSource::AnyFriendlyUnitInObjectRangeCheck checker(this, caster, 4.5f);
            WoWSource::UnitListSearcher<WoWSource::AnyFriendlyUnitInObjectRangeCheck> searcher(this, targets, checker);
            VisitNearbyObject(4.5f, searcher);

            for (Unit* target : targets)
            {
                if (!target->HasAura(145629))
                {
                    if (AuraPtr aura = caster->AddAura(145629, target))
                        aura->SetDuration(_duration);
                }
            }
            break;
        }
        case 13810: // Ice Trap
        {
            UnitList targetList;
            radius = 10.0f;
            
            enum eSpells
            {
                SPELL_HUN_ICE_TRAP_SLOW_EFFECT  = 135299,
                SPELL_HUN_GLYPH_OF_BLACK_ICE    = 109263,
                SPELL_HUN_BLACK_ICE_SPEED_EFFECT = 83559
            };

            /*************************************************************************************************
             *          APLICAR EL LENTEO A LOS ENEMIGOS QUE ENTREN EN LA TRAMPA 
             ************************************************************************************************/
            WoWSource::NearestAttackableUnitInObjectRangeCheck targets_check(this, caster, radius);
            WoWSource::UnitListSearcher<WoWSource::NearestAttackableUnitInObjectRangeCheck> targets_searcher(this, targetList, targets_check);
            VisitNearbyObject(radius, targets_searcher);

            if (!targetList.empty())
            {
                for (auto target : targetList)
                {
                    if (caster->IsValidAttackTarget(target))
                        target->CastSpell(target, eSpells::SPELL_HUN_ICE_TRAP_SLOW_EFFECT, true);
                }
            }

            /*************************************************************************************************
            *          APLICAR BUFF DE VELOCIDAD DEL GLIFO DE SUELO RESBALADIZO AL CASTER SI ESTA EN RANGO
            *************************************************************************************************/
            UnitList friendlyList;
            bool affectedBySpeed = false;

            WoWSource::AnyFriendlyUnitInObjectRangeCheck friendly_check(this, caster, radius);
            WoWSource::UnitListSearcher<WoWSource::AnyFriendlyUnitInObjectRangeCheck> friendly_searcher(this, friendlyList, friendly_check);
            VisitNearbyObject(radius, friendly_searcher);

            if (!friendlyList.empty())
            {
                for (auto friendly : friendlyList)
                {
                    //Si esta dentro del rango le casteamos la velocidad
                    if (friendly->GetGUID() == caster->GetGUID() && caster->HasAura(eSpells::SPELL_HUN_GLYPH_OF_BLACK_ICE))
                    {
                        if (!caster->HasAura(eSpells::SPELL_HUN_BLACK_ICE_SPEED_EFFECT))
                        {
                            caster->AddAura(eSpells::SPELL_HUN_BLACK_ICE_SPEED_EFFECT, caster, caster->GetGUID());
                            affectedBySpeed = true;
                        }

                        return;
                    }
                }
            }

            //Si esta fuera del rango le eliminamos la velocidad
            if (!affectedBySpeed && caster->HasAura(eSpells::SPELL_HUN_BLACK_ICE_SPEED_EFFECT))
                caster->RemoveAura(eSpells::SPELL_HUN_BLACK_ICE_SPEED_EFFECT);

            break;
        }
        case 109337: // Frostflake Snare Hagara Stormbraker
        {
             std::list<Unit*> targetList;
             radius = 10.0f;

             WoWSource::NearestAttackableUnitInObjectRangeCheck u_check(this, caster, radius);
             WoWSource::UnitListSearcher<WoWSource::NearestAttackableUnitInObjectRangeCheck> searcher(this, targetList, u_check);
             VisitNearbyObject(radius, searcher);

             if (!targetList.empty())
             for (auto itr : targetList)
                 itr->CastSpell(itr, 110316, true); //Frostflake Snare Aura

             break;
        }
        case 102793: // Ursol's Vortex
        {
            std::list<Unit*> targetList;
            radius = 8.0f;

            WoWSource::NearestAttackableUnitInObjectRangeCheck u_check(this, caster, radius);
            WoWSource::UnitListSearcher<WoWSource::NearestAttackableUnitInObjectRangeCheck> searcher(this, targetList, u_check);
            VisitNearbyObject(radius, searcher);

            if (!targetList.empty())
                for (auto itr : targetList)
                    if (caster->IsValidAttackTarget(itr))
                        if (!itr->HasAura(127797) && !itr->HasAura(102794))
                            caster->CastSpell(itr, 127797, true);

            break;
        }
        case 62618: // Power Word: Barrier
        {
            UnitList targetList;
            bool affected = false;
            radius = 4.5f;
            WoWSource::AnyFriendlyUnitInObjectRangeCheck u_check(this, caster, radius);
            WoWSource::UnitListSearcher<WoWSource::AnyFriendlyUnitInObjectRangeCheck> searcher(this, targetList, u_check);
            VisitNearbyObject(radius, searcher);

            if (!targetList.empty())
            {
                for (auto itr : targetList)
                {
                    if (itr->GetGUID() == caster->GetGUID())
                    {
                        caster->CastSpell(itr, 81782, true);
                        affected = true;

                        return;
                    }
                }
            }

            if (!affected)
                caster->RemoveAura(81782);

            break;
        }
        case 144692: // Pool of Fire Ordos
        {
            std::list<Player*> targetList;
            radius = 15.0f; // Not sure, needs check.

            GetPlayerListInGrid(targetList, 200.0f);

            if (!targetList.empty())
            {
                for (auto itr : targetList)
                {
                    // Pool of Fire - Periodic Damage
                    if (itr->GetDistance(this) > radius)
                        itr->RemoveAurasDueToSpell(144693);
                    else if (!itr->HasAura(144693))
                        caster->AddAura(144693, itr);
                }
            }
            break;
        }
        case 115460: // Healing Sphere
        {
            std::list<Unit*> targetList;
            radius = 1.0f;

            WoWSource::AnyFriendlyUnitInObjectRangeCheck u_check(this, caster, radius);
            WoWSource::UnitListSearcher<WoWSource::AnyFriendlyUnitInObjectRangeCheck> searcher(this, targetList, u_check);
            VisitNearbyObject(radius, searcher);

            if (!targetList.empty())
            {
                for (auto itr : targetList)
                {
                    if (itr->GetHealthPct() < 100.0f && caster->IsInRaidWith(itr))
                    {
                        if (caster->_IsValidAssistTarget(itr, sSpellMgr->GetSpellInfo(115464)))
                        {
                            caster->CastSpell(itr, 115464, true); // Healing Sphere heal
                            if (caster->HasAura(145439))
                            {
                                int32 amount = caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.3375f;
                                caster->CastCustomSpell(145441, SPELLVALUE_BASE_POINT0, amount, itr, true);
                            }
                            RemovedByExpired = false;
                            SetDuration(0);

                            // we should remove stack from caster healing sphere counter
                            if (AuraPtr healingSphereBuff = caster->GetAura(124458, caster->GetGUID()))
                            {
                                if (healingSphereBuff->GetStackAmount() > 1)
                                    healingSphereBuff->SetStackAmount(healingSphereBuff->GetStackAmount() - 1);
                                else
                                    caster->RemoveAura(healingSphereBuff);
                            }

                            return;
                        }
                    }
                }
            }

            break;
        }
        case 115817: // Cancel Barrier
        {
            std::list<Unit*> targetList;
            radius = 100.0f;

            WoWSource::AnyFriendlyUnitInObjectRangeCheck u_check(this, caster, radius);
            WoWSource::UnitListSearcher<WoWSource::AnyFriendlyUnitInObjectRangeCheck> searcher(this, targetList, u_check);
            VisitNearbyObject(radius, searcher);

            if (!targetList.empty())
                for (auto itr : targetList)
                {
                    if (itr->GetDistance(caster) > 6.0f)
                        itr->RemoveAurasDueToSpell(115856);
                    else
                        itr->AddAura(115856, itr);
                }

            break;
        }
        case 116011: // Rune of Power
        {
            std::list<Unit*> targetList;
            bool affected = false;
            radius = 2.25f;

            WoWSource::AnyFriendlyUnitInObjectRangeCheck u_check(this, caster, radius);
            WoWSource::UnitListSearcher<WoWSource::AnyFriendlyUnitInObjectRangeCheck> searcher(this, targetList, u_check);
            VisitNearbyObject(radius, searcher);

            if (!targetList.empty())
            {
                for (auto itr : targetList)
                {
                    if (itr->GetGUID() == caster->GetGUID())
                    {
                        caster->CastSpell(itr, 116014, true); // Rune of Power
                        affected = true;

                        if (caster->ToPlayer())
                            caster->ToPlayer()->UpdateManaRegen();

                        return;
                    }
                }
            }

            if (!affected)
                caster->RemoveAura(116014);

            break;
        }
        case 116235: // Amethyst Pool
        {
            std::list<Unit*> targetList;
            radius = 10.0f;

            WoWSource::NearestAttackableUnitInObjectRangeCheck u_check(this, caster, radius);
            WoWSource::UnitListSearcher<WoWSource::NearestAttackableUnitInObjectRangeCheck> searcher(this, targetList, u_check);
            VisitNearbyObject(radius, searcher);

            if (!targetList.empty())
            {
                for (auto itr : targetList)
                {
                    // Amethyst Pool - Periodic Damage
                    if (itr->GetDistance(this) > 3.5f)
                        itr->RemoveAura(130774);
                    else if (!itr->HasAura(130774))
                        caster->CastSpell(itr, 130774, true);
                }
            }

            break;
        }
        case 123461: // Get Away!
        {
            std::list<Player*> playerList;
            GetPlayerListInGrid(playerList, 60.0f);

            Position pos;
            GetPosition(&pos);

            if (!playerList.empty())
            {
                for (Player* l_Player : playerList)
                {
                    if (l_Player->IsWithinDist(caster, 40.0f, false))
                    {

                        if (l_Player->isAlive() && !l_Player->GetForcedMovement().IsActive())
                        {
                            l_Player->GetForcedMovement().StartPushingFrom(pos, 3.0f);

                        }
                        else if (!l_Player->isAlive() && l_Player->GetForcedMovement().IsActive())
                            l_Player->GetForcedMovement().Stop();
                    }
                    else if (l_Player->GetForcedMovement().IsActive())
                        l_Player->GetForcedMovement().Stop();
                }
            }

            break;
        }
        case 121284: // Gusting Winds From him Wing Leader Neronok
        case 121282: // Gusting Winds Towards him Wing Leader Neronok
        {
            std::list<Player*> playerList;
            GetPlayerListInGrid(playerList, 150.0f);

            Position pos;
            caster->GetPosition(&pos);

            if (!playerList.empty())
            {
                for (Player* l_Player : playerList)
                {
                    if (l_Player->IsWithinDist(caster, 150.0f, false))
                    {
                        if (l_Player->isAlive() && !l_Player->GetForcedMovement().IsActive())
                        {
                            l_Player->GetForcedMovement().StartPushingFrom(pos, 9.0f);
                        }
                        else if (!l_Player->isAlive() && l_Player->GetForcedMovement().IsActive())
                            l_Player->GetForcedMovement().Stop();
                    }
                    else if (l_Player->GetForcedMovement().IsActive())
                        l_Player->GetForcedMovement().Stop();
                }
            }
            break;
        }
        case 116546: // Draw Power
        {
            std::list<Unit*> targetList;
            radius = 30.0f;

            WoWSource::NearestAttackableUnitInObjectRangeCheck u_check(this, caster, radius);
            WoWSource::UnitListSearcher<WoWSource::NearestAttackableUnitInObjectRangeCheck> searcher(this, targetList, u_check);
            VisitNearbyObject(radius, searcher);

            if (!targetList.empty())
            {
                for (auto itr : targetList)
                {
                    if (GetCaster()->isInFront(itr, M_PI / 8))
                    {
                        if (!itr->HasAura(116663))
                            caster->AddAura(116663, itr);
                    }
                    else
                        itr->RemoveAurasDueToSpell(116663);
                }
            }

            break;
        }
        case 117032: // Healing Sphere (Afterlife)
        {
            std::list<Unit*> targetList;
            radius = 1.0f;

            WoWSource::AnyFriendlyUnitInObjectRangeCheck u_check(this, caster, radius);
            WoWSource::UnitListSearcher<WoWSource::AnyFriendlyUnitInObjectRangeCheck> searcher(this, targetList, u_check);
            VisitNearbyObject(radius, searcher);

            if (!targetList.empty())
            {
                for (auto itr : targetList)
                {
                    if (itr->GetGUID() == caster->GetGUID() && itr->GetHealthPct() < 100.0f)
                    {
                        if (caster->_IsValidAssistTarget(itr, sSpellMgr->GetSpellInfo(125355)))
                        {
                            caster->CastSpell(itr, 125355, true); // Heal for 15% of life

                            // we should remove stack from caster healing sphere counter
                            if (AuraPtr healingSphereBuff = caster->GetAura(124458, caster->GetGUID()))
                            {
                                if (healingSphereBuff->GetStackAmount() > 1)
                                    healingSphereBuff->SetStackAmount(healingSphereBuff->GetStackAmount() - 1);
                                else
                                    caster->RemoveAura(healingSphereBuff);
                            }
                            RemovedByExpired = false;
                            SetDuration(0);
                            return;
                        }
                    }
                }
            }

            break;
        }
        case 119031: // Gift of the Serpent (Mastery)
        {
            std::list<Unit*> targetList;
            radius = 1.0f;

            WoWSource::AnyFriendlyUnitInObjectRangeCheck u_check(this, caster, radius);
            WoWSource::UnitListSearcher<WoWSource::AnyFriendlyUnitInObjectRangeCheck> searcher(this, targetList, u_check);
            VisitNearbyObject(radius, searcher);

            if (!targetList.empty())
            {
                for (auto itr : targetList)
                {
                    if (itr->GetHealthPct() < 100.0f)
                    {
                        if (caster->_IsValidAssistTarget(itr, sSpellMgr->GetSpellInfo(124041)))
                        {
                            caster->CastSpell(itr, 124041, true); // Gift of the Serpent heal
                            RemovedByExpired = false;
                            SetDuration(0);
                            return;
                        }
                    }
                }
            }

            break;
        }
        case 121286: // Chi Sphere (Afterlife)
        {
            std::list<Unit*> targetList;
            radius = 1.0f;

            WoWSource::AnyFriendlyUnitInObjectRangeCheck u_check(this, caster, radius);
            WoWSource::UnitListSearcher<WoWSource::AnyFriendlyUnitInObjectRangeCheck> searcher(this, targetList, u_check);
            VisitNearbyObject(radius, searcher);

            if (!targetList.empty())
            {
                for (auto itr : targetList)
                {
                    if (itr->GetGUID() == caster->GetGUID())
                    {
                        if (itr->GetPower(POWER_CHI) < itr->GetMaxPower(POWER_CHI))
                        {
                            caster->CastSpell(itr, 121283, true); // Restore 1 Chi
                            SetDuration(0);
                            return;
                        }
                    }
                }
            }

            break;
        }
        case 138310:
        {
            std::list<Unit*> targetList;
            radius = 1.0f;

            WoWSource::AnyFriendlyUnitInObjectRangeCheck u_check(this, caster, radius);
            WoWSource::UnitListSearcher<WoWSource::AnyFriendlyUnitInObjectRangeCheck> searcher(this, targetList, u_check);
            VisitNearbyObject(radius, searcher);

            if (!targetList.empty())
            {
                for (auto itr : targetList)
                {
                    if (itr->GetGUID() == caster->GetGUID())
                    {
                        caster->CastSpell(itr, 138311, true);
                        SetDuration(0);
                        return;
                    }
                }
            }

            break;
        }
        case 121536: // Angelic Feather
        {
            std::list<Unit*> targetList;
            radius = 1.0f;

            WoWSource::AnyFriendlyUnitInObjectRangeCheck u_check(this, caster, radius);
            WoWSource::UnitListSearcher<WoWSource::AnyFriendlyUnitInObjectRangeCheck> searcher(this, targetList, u_check);
            VisitNearbyObject(radius, searcher);

            if (!targetList.empty())
            {
                for (auto itr : targetList)
                {
                    if (caster->_IsValidAssistTarget(itr, sSpellMgr->GetSpellInfo(121557)))
                    {
                        caster->CastSpell(itr, 121557, true); // Angelic Feather increase speed
                        SetDuration(0);
                        return;
                    }
                }
            }

            break;
        }
        case 122035: // Path of Blossom
        {
            std::list<Unit*> targetList;
            radius = 1.0f;

            WoWSource::NearestAttackableUnitInObjectRangeCheck u_check(this, caster, radius);
            WoWSource::UnitListSearcher<WoWSource::NearestAttackableUnitInObjectRangeCheck> searcher(this, targetList, u_check);
            VisitNearbyObject(radius, searcher);

            if (!targetList.empty())
            {
                for (auto itr : targetList)
                {
                    caster->CastSpell(itr, 122036, true); // Path of Blossom damage
                    SetDuration(0);
                    return;
                }
            }

            break;
        }
        case 124503: // Gift of the Ox - Right
        case 124506: // Gift of the Ox - Left
        {
            std::list<Unit*> targetList;
            radius = 1.0f;

            WoWSource::AnyFriendlyUnitInObjectRangeCheck u_check(this, caster, radius);
            WoWSource::UnitListSearcher<WoWSource::AnyFriendlyUnitInObjectRangeCheck> searcher(this, targetList, u_check);
            VisitNearbyObject(radius, searcher);

            if (!targetList.empty())
            {
                for (auto itr : targetList)
                {
                    if (itr->GetGUID() != caster->GetGUID())
                        continue;
                
                    caster->CastSpell(itr, 124507, true); // Gift of the Ox - Heal
                    SetDuration(0);
                    return;
                }
            }

            break;
        }

        // Heart of Fear.

        case 123811: // Pheromones of Zeal Zor'lok
        {
            std::list<Player*> targetList;
            radius = 100.0f;
            float zPos = 407.0f;

            GetPlayerListInGrid(targetList, 200.0f);

            if (!targetList.empty())
            {
                for (auto player : targetList)
                {
                    // Pheromones of Zeal - Periodic Damage
                    if (player->GetDistance(this) > radius || player->GetPositionZ() > zPos)
                        player->RemoveAurasDueToSpell(123812);
                    else
                    {
					    if (!player->HasAura(123812))
                            caster->AddAura(123812, player);
                    }
                }
            }
            break;
        }
        case 122731: // Create Cancelling Noise Area trigger
        {
            std::list<Unit*> targetList;
            radius = 10.0f;

            WoWSource::NearestAttackableUnitInObjectRangeCheck u_check(this, caster, radius);
            WoWSource::UnitListSearcher<WoWSource::NearestAttackableUnitInObjectRangeCheck> searcher(this, targetList, u_check);
            VisitNearbyObject(radius, searcher);

            if (!targetList.empty())
            {
                for (auto itr : targetList)
                {
                    // Periodic absorption for Imperial Vizier Zor'lok's Force and Verve and Sonic Rings
                    if (itr->GetDistance(this) > 2.0f)
                        itr->RemoveAura(122706);
                    else if (!itr->HasAura(122706))
                        caster->AddAura(122706, itr);
                }
            }
            break;
        }

        // Siege of Orgrimmar.

        case 143235: // Noxious Poison He Softfoot
        {
            std::list<Player*> targetList;
            radius = 3.5f;

            GetPlayerListInGrid(targetList, 100.0f);

            if (!targetList.empty())
            {
                for (auto itr : targetList)
                {
                    // Noxious Poison - Periodic Damage
                    if (itr->GetDistance(this) > radius)
                        itr->RemoveAurasDueToSpell(143239);
                    else
                    {
                        if (!itr->HasAura(143239))
                            caster->AddAura(143239, itr);
                    }
                }
            }
            break;
        }
        case 143546: // Dark Meditation Sun Tenderheart
        {
            std::list<Player*> targetList;
            radius = 10.0f;

            GetPlayerListInGrid(targetList, 100.0f);

            if (!targetList.empty())
            {
                for (auto itr : targetList)
                {
                    // Dark Meditation - Damage Reduction
                    if (itr->GetDistance(this) > radius)
                        itr->RemoveAurasDueToSpell(143564);
                    else
                    {
                        if (!itr->HasAura(143564))
                            caster->AddAura(143564, itr);
                    }
                }
            }
            break;
        }
        case 143960: // Defiled Ground Embodied Misery
        {
            std::list<Player*> targetList;
            radius = 4.0f;

            GetPlayerListInGrid(targetList, 100.0f);

            if (!targetList.empty())
            {
                for (auto itr : targetList)
                {
                    // Defiled Ground - Periodic Damage
                    if (itr->GetDistance(this) > radius)
                        itr->RemoveAurasDueToSpell(143959);
                    else
                    {
                        if (!itr->HasAura(143959))
                            caster->AddAura(143959, itr);
                    }
                }
            }
            break;
        }

        case 146793: // Bottomless Pit Greater Corruption
        {
            std::list<Player*> targetList;
            radius = 4.0f;

            GetPlayerListInGrid(targetList, 100.0f);

            if (!targetList.empty())
            {
                for (auto itr : targetList)
                {
                    // Bottomless Pit - Periodic Damage
                    if (itr->GetDistance(this) > radius)
                        itr->RemoveAurasDueToSpell(146703);
                    else
                    {
                        if (!itr->HasAura(146703))
                            caster->AddAura(146703, itr);
                    }
                }
            }
            break;
        }
		case 115290: // Spirit Gale
		{
			std::list<Player*> targetList;
			radius = 2.0f;

			GetPlayerListInGrid(targetList, 100.0f);

			if (!targetList.empty())
			{
				for (auto itr : targetList)
				{
					// Spirit Gale - Periodic Damage
					if (itr->GetDistance(this) > radius)
						itr->RemoveAurasDueToSpell(115291);
					else
					{
						if (!itr->HasAura(115291))
							itr->CastSpell(itr, 115291, false);
					}
				}
			}
			break;
		}

        default: break;
    }
}

void AreaTrigger::Remove()
{
    if (IsInWorld())
    {
        SpellInfo const* m_spellInfo = sSpellMgr->GetSpellInfo(GetUInt32Value(AREATRIGGER_SPELLID));
        if (!m_spellInfo)
            return;

        switch (m_spellInfo->Id)
        {
            case 13810: // Ice Trap
            {
                enum eSpells
                {
                    SPELL_HUN_ICE_TRAP_SLOW_EFFECT = 135299,
                    SPELL_HUN_GLYPH_OF_BLACK_ICE = 109263,
                    SPELL_HUN_BLACK_ICE_SPEED_EFFECT = 83559
                };
                
                if (m_caster && m_caster->HasAura(eSpells::SPELL_HUN_BLACK_ICE_SPEED_EFFECT))
                    m_caster->RemoveAura(eSpells::SPELL_HUN_BLACK_ICE_SPEED_EFFECT);

                break;
            }
            case 115460: // Healing sphere
            case 117032: // Healing Sphere (Afterlife)
            {
                if (!RemovedByExpired)
                    break;

                if (!m_caster)
                    break;

                m_caster->CastSpell(GetPositionX(), GetPositionY(), GetPositionZ(), 135914, true);
                break;
            }
            case 119031: // Gift of the Serpent (Mastery)
            {
                if (!RemovedByExpired)
                    break;

                if (!m_caster)
                    break;

                m_caster->CastSpell(GetPositionX(), GetPositionY(), GetPositionZ(), 135920, true);
                break;
            }
            case 62618: // Power Word: Barrier
                if (m_caster && m_caster->HasAura(81782))
                    m_caster->RemoveAura(81782);
                break;
            case 116011: // Rune of Power
                if (m_caster && m_caster->HasAura(116014))
                    m_caster->RemoveAura(116014);
                break;
            case 115817:// Cancel Barrier
                {
                    std::list<Player*> targetList;
                    GetPlayerListInGrid(targetList, 100.0f);

                    if (!targetList.empty())
                        for (auto itr : targetList)
                            itr->RemoveAurasDueToSpell(115856);
                    break;
                }
            case 144692: // Pool of Fire Ordos
            {
                std::list<Player*> targetList;
                GetPlayerListInGrid(targetList, 100.0f);

                if (!targetList.empty())
                    for (auto itr : targetList)
                        itr->RemoveAurasDueToSpell(144693); // Pool of Fire - Periodic Damage Remove.
                break;
            }
            case 123461: // Get Away!
            {
                std::list<Player*> playerList;
                GetPlayerListInGrid(playerList, 100.0f);

                Position pos;
                GetPosition(&pos);

                if (!playerList.empty())
                for (Player* l_Player : playerList)
                    l_Player->GetForcedMovement().Stop();
                break;
            }

            case 121282: // Gusting Winds
            case 121284:
            {
                std::list<Player*> playerList;
                GetPlayerListInGrid(playerList, 60.0f);

                Position pos;
                GetPosition(&pos);

                if (!playerList.empty())
                for (Player* l_Player : playerList)
                    l_Player->GetForcedMovement().Stop();

                break;
            }

            // Heart of Fear.

            case 123811: // Pheromones of Zeal Zor'lok
            {
                std::list<Player*> targetList;
                GetPlayerListInGrid(targetList, 200.0f);

                if (!targetList.empty())
                    for (auto itr : targetList)
                        itr->RemoveAurasDueToSpell(123812); // Pheromones of Zeal - Periodic Damage Remove.
                break;
            }
            case 122731: // Create Noise Cancelling Area Trigger
            {
                std::list<Player*> playerList;
                GetPlayerListInGrid(playerList, 200.0f);

                if (!playerList.empty())
                    for (auto player : playerList)
                        if (player->HasAura(122706))
                            player->RemoveAura(122706);
                break;
            }

            // Siege of Orgrimmar.

            case 143235: // Noxious Poison He Softfoot
            {
                std::list<Player*> targetList;
                GetPlayerListInGrid(targetList, 100.0f);

                if (!targetList.empty())
                    for (auto itr : targetList)
                        itr->RemoveAurasDueToSpell(143239);
                break;
            }
            case 143546: // Dark Meditation Sun Tenderheart
            {
                std::list<Player*> targetList;
                GetPlayerListInGrid(targetList, 100.0f);

                if (!targetList.empty())
                    for (auto itr : targetList)
                        itr->RemoveAurasDueToSpell(143564);
                break;
            }
            case 143960: // Defiled Ground Embodied Misery
            {
                std::list<Player*> targetList;
                GetPlayerListInGrid(targetList, 100.0f);

                if (!targetList.empty())
                    for (auto itr : targetList)
                        itr->RemoveAurasDueToSpell(143959);
                break;
            }

            case 146793: // Bottomless Pit Greater Corruption
            {
                std::list<Player*> targetList;
                GetPlayerListInGrid(targetList, 100.0f);

                if (!targetList.empty())
                    for (auto itr : targetList)
                        itr->RemoveAurasDueToSpell(146703);
                break;
            }

			case 115290:  // Spirit Gale
			{
				std::list<Player*> targetList;
				GetPlayerListInGrid(targetList, 100.0f);

				if (!targetList.empty())
					for (auto itr : targetList)
						itr->RemoveAurasDueToSpell(115291);
				break;
			}

            default: break;
        }

        SendObjectDeSpawnAnim(GetGUID());
        RemoveFromWorld();
        AddObjectToRemoveList();
    }
}

void AreaTrigger::BindToCaster()
{
    m_caster = ObjectAccessor::GetUnit(*this, GetCasterGUID());

    if (m_caster)
        m_caster->_RegisterAreaTrigger(this);
}

void AreaTrigger::UnbindFromCaster()
{
    ASSERT(m_caster);
    m_caster->_UnregisterAreaTrigger(this);
    m_caster = NULL;
}
