#pragma once

#include "common.h"
#include "formats/pbak.h"
#include "ns.h"

extern int PbakInit();
extern int PbakKill();
extern void PbakPlay(eid_t *);
extern void PbakChoose(eid_t *);
