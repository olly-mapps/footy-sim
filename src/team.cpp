#include "team.h"

Team::Team(int skill) : skillStat(skill) {}

int Team::getSkillStat() const {
    return skillStat;
}