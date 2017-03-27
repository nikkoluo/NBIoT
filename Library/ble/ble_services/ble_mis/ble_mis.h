/** @file
 *
 * @defgroup ble_sdk_srv_mis Mi Service
 * @{
 * @ingroup ble_sdk_srv
 * @brief Mi Service module.
 *
 * @details This module implements the Mi Service with the Xiaomi characteristic.
 *          During initialization it adds the Mi Service to the BLE stack database. 
 *
 *
 * @note The application must propagate BLE stack events to the Mi Service module by calling
 *       ble_mis_on_ble_evt() from the @ref softdevice_handler callback.
 *
 */

#ifndef BLE_MIS_H__
#define BLE_MIS_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"


/*
 * Definition for BLE device relationship.
 */
#define MIIO_BLE_DEV_RELATION_WEAK                    0
#define MIIO_BLE_DEV_RELATION_STRONG                  1



#define BLE_UUID_MI_SERVICE                           0xFE95     /**< Mi service UUID. */



/**
 * Characteristic UUID
 */
// Mi Service Common Characteristics
#define MISERVICE_CHAR_TOKEN_UUID                     0x0001
#define MISERVICE_CHAR_PRODUCTID_UUID                 0x0002
#define MISERVICE_CHAR_VER_UUID                       0x0004
#define MISERVICE_CHAR_WIFIAPSSID_UUID                0x0005
#define MISERVICE_CHAR_WIFIAPPW_UUID                  0x0006
#define MISERVICE_CHAR_EVENT_RULE_UUID                0x0007
#define MISERVICE_CHAR_AUTHENTICATION_UUID            0x0010
#define MISERVICE_CHAR_SN_UUID                        0x0013
#define MISERVICE_CHAR_BEACONKEY_UUID                 0x0014


// Events Characteristics
#define MISERVICE_CHAR_KEY_CLIENT_UUID                0x1001
#define MISERVICE_CHAR_KEY_SERVER_UUID                0x1002
#define MISERVICE_CHAR_SLEEP_CLIENT_UUID              0x1003
#define MISERVICE_CHAR_SLEEP_SERVER_UUID              0x1004



#define MIIO_BLE_VER_LEN                              10



/**@brief Mi Service event type. */
typedef enum
{
    BLE_MIS_EVT_BOND_SUCC,                             /**< Mi Service bond succeed event. */
    BLE_MIS_EVT_BOND_FAIL                              /**< Mi Service bond failed event. */
} ble_mis_evt_type_t;

/**@brief Mi Service event. */
typedef struct
{
    ble_mis_evt_type_t evt_type;                                  /**< Type of event. */
} ble_mis_evt_t;


// Forward declaration of the ble_mis_t type. 
typedef struct ble_mis_s ble_mis_t;

/**@brief Mi Service event handler type. */
typedef void (*ble_mis_evt_handler_t) (ble_mis_evt_type_t evt, uint16_t conn_handle);

/**@brief Flash Write function type. */
typedef int (*miservice_flash_writeFunc_t)(uint32_t addr, uint8_t* data, uint16_t len);

/**@brief Flash Read function type. */
typedef int (*miservice_flash_readFunc_t)(uint32_t addr, uint8_t* data, uint16_t len);


/**@brief Mi Service init structure. This contains all options and data needed for
 *        initialization of the service.*/
typedef struct
{
    ble_mis_evt_handler_t         evt_handler;                    /**< Event handler to be called for handling events in the Mi Service. */
    uint16_t                      productId;                      /**< Product ID. */
    uint8_t                       relation;                       /**< Relationship. */
    uint8_t                       version[MIIO_BLE_VER_LEN];      /**< Version. */
    miservice_flash_writeFunc_t   flashWriteFn;
    miservice_flash_readFunc_t    flashReadFn;
    uint32_t                      flashBaseAddr;

    ble_srv_report_ref_t *        p_report_ref;                   /**< If not NULL, a Report Reference descriptor with the specified value will be added to the Battery Level characteristic */
    ble_srv_security_mode_t       mis_attr_md;                 /**< Initial Security Setting for Device Information Characteristics. */
} ble_mis_init_t;

/**@brief Mi Service structure. This contains various status information for the service. */
struct ble_mis_s
{
    ble_mis_evt_handler_t         evt_handler;                    /**< Event handler to be called for handling events in the Battery Service. */
    uint16_t                      service_handle;                 /**< Handle of Mi Service (as provided by the BLE stack). */
    uint16_t                      report_ref_handle;              /**< Handle of the Report Reference descriptor. */
    uint16_t                      conn_handle;                    /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
    uint16_t                      productID;
    uint8_t                       relation;

    miservice_flash_writeFunc_t   flashWriteFn;
    miservice_flash_readFunc_t    flashReadFn;
    uint32_t                      flashBaseAddr;
};

/**@brief Function for initializing the Mi Service.
 *
 * @param[out]  p_mis       Mi Service structure. This structure will have to be supplied by
 *                          the application. It will be initialized by this function, and will later
 *                          be used to identify this particular service instance.
 * @param[in]   p_mis_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_mis_init(const ble_mis_init_t * p_mis_init);

/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Mi Service.
 *
 * @note For the requirements in the MIS specification to be fulfilled,
 *
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
void ble_mis_on_ble_evt(ble_evt_t * p_ble_evt);



#endif // BLE_MIS_H__

/** @} */

