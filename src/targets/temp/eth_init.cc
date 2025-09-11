#include "stm32h7xx_hal.h"
#include "lan8742.h"
#include <string.h>

ETH_HandleTypeDef heth;
ETH_TxPacketConfig TxConfig;
lan8742_Object_t LAN8742;

/* PHY address for LAN8742 on Nucleo-H753ZI board */
#define LAN8742_PHY_ADDRESS 0

void MX_ETH_Init(void)
{
    /* Configure ETH peripheral */
    heth.Instance = ETH;
    heth.Init.MACAddr[0] = 0x02;
    heth.Init.MACAddr[1] = 0x00;
    heth.Init.MACAddr[2] = 0x00;
    heth.Init.MACAddr[3] = 0x00;
    heth.Init.MACAddr[4] = 0x00;
    heth.Init.MACAddr[5] = 0x01;
    heth.Init.MediaInterface = HAL_ETH_RMII_MODE;
    heth.Init.TxDesc = NULL;   // HAL will allocate
    heth.Init.RxDesc = NULL;   // HAL will allocate
    heth.Init.RxBuffLen = 1524;

    if (HAL_ETH_Init(&heth) != HAL_OK) {
        // Init error: hang
        while (1);
    }

    /* Fill Tx config structure */
    memset(&TxConfig, 0, sizeof(ETH_TxPacketConfig));
    TxConfig.Attributes = ETH_TX_PACKETS_FEATURES_CSUM | ETH_TX_PACKETS_FEATURES_CRCPAD;
    TxConfig.ChecksumCtrl = ETH_CHECKSUM_IPHDR_PAYLOAD_INSERT_PHDR_CALC;
    TxConfig.CRCPadCtrl   = ETH_CRC_PAD_INSERT;

    /* Init PHY driver (LAN8742) */
    lan8742_Object_t obj;

    lan8742_IOCtx_t LAN8742_IOCtx;
    LAN8742_IOCtx.Init        = NULL;
    LAN8742_IOCtx.DeInit      = NULL;
    LAN8742_IOCtx.ReadReg     = HAL_ETH_ReadPHYRegister;
    LAN8742_IOCtx.WriteReg    = HAL_ETH_WritePHYRegister;
    LAN8742_IOCtx.GetTick     = HAL_GetTick;

    obj.DevAddr     = LAN8742_PHY_ADDRESS;

    if (LAN8742_RegisterBusIO(&LAN8742, &LAN8742_IOCtx) != LAN8742_STATUS_OK) {
        while (1);
    }

    if (LAN8742_Init(&LAN8742) != LAN8742_STATUS_OK) {
        while (1);
    }

    /* Optional: wait for link up */
    uint32_t phy_status;
    do {
        LAN8742_GetLinkState(&LAN8742, &phy_status);
    } while (phy_status == LAN8742_STATUS_LINK_DOWN);
}
