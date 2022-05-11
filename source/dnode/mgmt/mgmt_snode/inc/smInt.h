/*
 * Copyright (c) 2019 TAOS Data, Inc. <jhtao@taosdata.com>
 *
 * This program is free software: you can use, redistribute, and/or modify
 * it under the terms of the GNU Affero General Public License, version 3
 * or later ("AGPL"), as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _TD_DND_SNODE_INT_H_
#define _TD_DND_SNODE_INT_H_

#include "dmInt.h"

#include "snode.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SSnodeMgmt {
  SSnode       *pSnode;
  SMsgCb        msgCb;
  const char   *path;
  const char   *name;
  int32_t       dnodeId;
  SRWLatch      latch;
  int8_t        uniqueWorkerInUse;
  SArray       *uniqueWorkers;  // SArray<SMultiWorker*>
  SSingleWorker sharedWorker;
  SSingleWorker monitorWorker;
} SSnodeMgmt;

// smHandle.c
SArray *smGetMsgHandles();
int32_t smProcessCreateReq(SSnodeMgmt *pMgmt, SNodeMsg *pMsg);
int32_t smProcessDropReq(SSnodeMgmt *pMgmt, SNodeMsg *pMsg);
int32_t smProcessGetMonitorInfoReq(SSnodeMgmt *pMgmt, SNodeMsg *pReq);

// smWorker.c
int32_t smStartWorker(SSnodeMgmt *pMgmt);
void    smStopWorker(SSnodeMgmt *pMgmt);
int32_t smPutNodeMsgToMgmtQueue(SSnodeMgmt *pMgmt, SNodeMsg *pMsg);
int32_t smPutNodeMsgToUniqueQueue(SSnodeMgmt *pMgmt, SNodeMsg *pMsg);
int32_t smPutNodeMsgToSharedQueue(SSnodeMgmt *pMgmt, SNodeMsg *pMsg);
int32_t smPutNodeMsgToExecQueue(SSnodeMgmt *pMgmt, SNodeMsg *pMsg);
int32_t smPutNodeMsgToMonitorQueue(SSnodeMgmt *pMgmt, SNodeMsg *pMsg);

#ifdef __cplusplus
}
#endif

#endif /*_TD_DND_SNODE_INT_H_*/