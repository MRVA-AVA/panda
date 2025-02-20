#pragma once

#include "safety_declarations.h"

static void ava_rx_hook(const CANPacket_t *to_push) {
  (void)to_push;
  return;
}


static bool ava_tx_hook(const CANPacket_t *to_send) {
  (void)to_send;
  bool tx = true;
  return tx;
}

static int ava_fwd_hook(int bus_num, int addr) {
  (void)bus_num;
  (void)addr;
  int bus_fwd = -1;
  return bus_fwd;
}

static safety_config ava_init(uint16_t param) {
  (void)param;
  safety_config ret;
  static const CanMsg TESLA_TX_MSGS[] = {
    {0x488, 0, 4},  // DAS_steeringControl
    {0x45, 0, 8},   // STW_ACTN_RQ
    {0x45, 2, 8},   // STW_ACTN_RQ
    {0x2b9, 0, 8},  // DAS_control
  };
  static RxCheck tesla_rx_checks[] = {
    {.msg = {{0x2b9, 2, 8, .frequency = 25U}, { 0 }, { 0 }}},   // DAS_control
    {.msg = {{0x370, 0, 8, .frequency = 25U}, { 0 }, { 0 }}},   // EPAS_sysStatus
    {.msg = {{0x108, 0, 8, .frequency = 100U}, { 0 }, { 0 }}},  // DI_torque1
    {.msg = {{0x118, 0, 6, .frequency = 100U}, { 0 }, { 0 }}},  // DI_torque2
    {.msg = {{0x20a, 0, 8, .frequency = 50U}, { 0 }, { 0 }}},   // BrakeMessage
    {.msg = {{0x368, 0, 8, .frequency = 10U}, { 0 }, { 0 }}},   // DI_state
    {.msg = {{0x318, 0, 8, .frequency = 10U}, { 0 }, { 0 }}},   // GTW_carState
  };
  ret = BUILD_SAFETY_CFG(tesla_rx_checks, TESLA_TX_MSGS);
  return ret;
}

const safety_hooks ava_hooks = {
  .init = ava_init,
  .rx = ava_rx_hook,
  .tx = ava_tx_hook,
  .fwd = ava_fwd_hook,
};
