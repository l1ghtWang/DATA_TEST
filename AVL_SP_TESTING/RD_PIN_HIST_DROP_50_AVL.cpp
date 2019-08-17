/*BEGIN_LEGAL 
Intel Open Source License 

Copyright (c) 2002-2016 Intel Corporation. All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.  Redistributions
in binary form must reproduce the above copyright notice, this list of
conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.  Neither the name of
the Intel Corporation nor the names of its contributors may be used to
endorse or promote products derived from this software without
specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE INTEL OR
ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
END_LEGAL */
//
// @ORIGINAL_AUTHOR: Artur Klauser
// @EXTENDED: Rodric Rabbah (rodric@gmail.com)
//

/*! @file
 *  This file contains an ISA-portable cache simulator
 *  data cache hierarchies
 */
#include "MurmurHash3.cpp"
#include "pin.H"
#include "AVL_SP.H"
#include <iostream>
#include <fstream>

#include "dcache.H"
#include "pin_profile.H"

std::ofstream outFile;
std::ofstream outFile2;

/* ===================================================================== */
/* Commandline Switches */
/* ===================================================================== */

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
                            "o", "dcache.out", "specify dcache file name");
KNOB<string> KnobOutputFile2(KNOB_MODE_WRITEONCE, "pintool",
                            "o2", "dcache.out", "specify dcache file name");
KNOB<BOOL> KnobTrackLoads(KNOB_MODE_WRITEONCE, "pintool",
                          "tl", "1", "track individual loads -- increases profiling time");
KNOB<BOOL> KnobTrackStores(KNOB_MODE_WRITEONCE, "pintool",
                           "ts", "1", "track individual stores -- increases profiling time");
KNOB<UINT32> KnobThresholdHit(KNOB_MODE_WRITEONCE, "pintool",
                              "rh", "100", "only report memops with hit count above threshold");
KNOB<UINT32> KnobThresholdMiss(KNOB_MODE_WRITEONCE, "pintool",
                               "rm", "100", "only report memops with miss count above threshold");
KNOB<UINT32> KnobCacheSize(KNOB_MODE_WRITEONCE, "pintool",
                           "c", "32", "cache size in kilobytes");
KNOB<UINT32> KnobLineSize(KNOB_MODE_WRITEONCE, "pintool",
                          "b", "32", "cache block size in bytes");
KNOB<UINT32> KnobAssociativity(KNOB_MODE_WRITEONCE, "pintool",
                               "a", "4", "cache associativity (1 for direct mapped)");
long long counter = 0;

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

INT32 Usage()
{
  cerr << "This tool represents a cache simulator.\n"
          "\n";

  cerr << KNOB_BASE::StringKnobSummary() << endl;
  return -1;
}

/* ===================================================================== */
/* Global Variables */
/* ===================================================================== */

// wrap configuation constants into their own name space to avoid name clashes
namespace DL1
{
const UINT32 max_sets = KILO;         // cacheSize / (lineSize * associativity);
const UINT32 max_associativity = 256; // associativity;
const CACHE_ALLOC::STORE_ALLOCATION allocation = CACHE_ALLOC::STORE_ALLOCATE;

typedef CACHE_ROUND_ROBIN(max_sets, max_associativity, allocation) CACHE;
} // namespace DL1

DL1::CACHE *dl1 = NULL;

typedef enum
{
  COUNTER_MISS = 0,
  COUNTER_HIT = 1,
  COUNTER_NUM
} COUNTER;

typedef COUNTER_ARRAY<UINT64, COUNTER_NUM> COUNTER_HIT_MISS;

// holds the counters with misses and hits
// conceptually this is an array indexed by instruction address
COMPRESSOR_COUNTER<ADDRINT, UINT32, COUNTER_HIT_MISS> profile;

/* ===================================================================== */

VOID LoadMulti(ADDRINT addr, UINT32 size, UINT32 instId)
{
  // first level D-cache
  const BOOL dl1Hit = dl1->Access(addr, size, CACHE_BASE::ACCESS_TYPE_LOAD);

  const COUNTER counter = dl1Hit ? COUNTER_HIT : COUNTER_MISS;
  profile[instId][counter]++;
}
//HAITANG---LOAD

VOID AVL(ADDRINT addr, UINT32 size, UINT32 instId)
{
  counter++;
  int seed = 998;
  long long ref1 = addr >> 6;
  long long ref2 = (addr + size - 1) >> 6;
  UINT32 hash1, hash2;
  MurmurHash3_x86_32(&ref1, 8, seed, &hash1);
  MurmurHash3_x86_32(&ref2, 8, seed, &hash2);

  uint32_t modulus = 1;
  modulus = modulus <<24;
  double dropRate = 0.5;
  uint32_t t = modulus * dropRate;

  if (((addr + size - 1) & 0x40) != (addr & 0x40))
  {

    if (hash1 % modulus > t)
      solve(ref1);
    if (hash2 % modulus > t)
      solve(ref2);
  }
  else
  {
    if (hash1 % modulus > t)
      solve(ref1);
  }
}

/* ===================================================================== */

VOID StoreMulti(ADDRINT addr, UINT32 size, UINT32 instId)
{
  // first level D-cache
  const BOOL dl1Hit = dl1->Access(addr, size, CACHE_BASE::ACCESS_TYPE_STORE);

  const COUNTER counter = dl1Hit ? COUNTER_HIT : COUNTER_MISS;
  profile[instId][counter]++;
}

/* ===================================================================== */

VOID LoadSingle(ADDRINT addr, UINT32 instId)
{
  // @todo we may access several cache lines for
  // first level D-cache
  const BOOL dl1Hit = dl1->AccessSingleLine(addr, CACHE_BASE::ACCESS_TYPE_LOAD);

  const COUNTER counter = dl1Hit ? COUNTER_HIT : COUNTER_MISS;
  profile[instId][counter]++;
}
/* ===================================================================== */

VOID StoreSingle(ADDRINT addr, UINT32 instId)
{
  // @todo we may access several cache lines for
  // first level D-cache
  const BOOL dl1Hit = dl1->AccessSingleLine(addr, CACHE_BASE::ACCESS_TYPE_STORE);

  const COUNTER counter = dl1Hit ? COUNTER_HIT : COUNTER_MISS;
  profile[instId][counter]++;
}

/* ===================================================================== */

VOID LoadMultiFast(ADDRINT addr, UINT32 size)
{
  dl1->Access(addr, size, CACHE_BASE::ACCESS_TYPE_LOAD);
}

/* ===================================================================== */

VOID StoreMultiFast(ADDRINT addr, UINT32 size)
{
  dl1->Access(addr, size, CACHE_BASE::ACCESS_TYPE_STORE);
}

/* ===================================================================== */

VOID LoadSingleFast(ADDRINT addr)
{
  dl1->AccessSingleLine(addr, CACHE_BASE::ACCESS_TYPE_LOAD);
}

/* ===================================================================== */

VOID StoreSingleFast(ADDRINT addr)
{
  dl1->AccessSingleLine(addr, CACHE_BASE::ACCESS_TYPE_STORE);
}

/* ===================================================================== */

VOID Instruction(INS ins, void *v)
{
  if (INS_IsMemoryRead(ins) && INS_IsStandardMemop(ins))
  {
    // map sparse INS addresses to dense IDs
    const ADDRINT iaddr = INS_Address(ins);

    const UINT32 instId = profile.Map(iaddr);

    //    size = INS_MemoryReadSize(ins);
    //    const BOOL   single = (size <= 4);
    //    outFile << KnobTrackLoads << endl;
    if (KnobTrackLoads)
    {

      INS_InsertPredicatedCall(
          ins, IPOINT_BEFORE, (AFUNPTR)AVL,
          IARG_MEMORYREAD_EA,
          IARG_MEMORYREAD_SIZE,
          IARG_UINT32, instId,
          IARG_END);
    }
  }

  if (INS_IsMemoryWrite(ins) && INS_IsStandardMemop(ins))
  {
    // map sparse INS addresses to dense IDs
    const ADDRINT iaddr = INS_Address(ins);

    const UINT32 instId = profile.Map(iaddr);

    //  size = INS_MemoryWriteSize(ins);

    //  const BOOL   single = (size <= 4);

    if (KnobTrackStores)
    {

      INS_InsertPredicatedCall(
          ins, IPOINT_BEFORE, (AFUNPTR)AVL,
          IARG_MEMORYWRITE_EA,
          IARG_MEMORYREAD_SIZE,
          IARG_UINT32, instId,
          IARG_END);
    }
  }
}
/* ===================================================================== */

VOID Fini(int code, VOID *v)
{

  // m = node_cnt*STEP;
  // double sum = 0; long long T = 0;
  //double tot = 0;
  // double N = tott+1.0*tott/(n-m)*m;
  //long long step = 1; int dom = 0,dT = 0; loc = 0;

  outFile << "reuse_distance,counts\n";
  int i = 0;
  for(i = 0; i< MAXL; i++)
  {
     outFile << (i)*rdInterval << "," << rd[i] << "\n";
  }

  solveMRC(rd);


  outFile2 << "cache_size,MRC\n";
  for(i = 0; i< MAXL; i++)
  {
     outFile2 << (i+1)*rdInterval << "," << mrc[i] << "\n";
  }


  outFile.close();
  outFile2.close();

}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(int argc, char *argv[])
{

  srand(time(NULL));
  PIN_InitSymbols();
  memset(rd, 0, sizeof(long long) * MAXL);
  if (PIN_Init(argc, argv))
  {
    return Usage();
  }

  cacheInit(&cache);

  outFile.open(KnobOutputFile.Value().c_str());
  outFile2.open(KnobOutputFile2.Value().c_str());

  dl1 = new DL1::CACHE("L1 Data Cache",
                       KnobCacheSize.Value() * KILO,
                       KnobLineSize.Value(),
                       KnobAssociativity.Value());

  profile.SetKeyName("iaddr          ");
  profile.SetCounterName("dcache:miss        dcache:hit");

  COUNTER_HIT_MISS threshold;

  threshold[COUNTER_HIT] = KnobThresholdHit.Value();
  threshold[COUNTER_MISS] = KnobThresholdMiss.Value();

  profile.SetThreshold(threshold);

  INS_AddInstrumentFunction(Instruction, 0);
  PIN_AddFiniFunction(Fini, 0);

  // Never returns

  PIN_StartProgram();

  return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
