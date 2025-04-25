#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

// Configuration Section (Modify these values)
#define AP_SSID       "test_wifi"          // AP name
#define AP_PASSWORD   "11223344@Aa"        // Password (min 8 chars for WPA2/WPA3)
#define AP_SECURITY_MODE WIFI_AUTH_WPA_PSK // Options: WIFI_AUTH_WPA_PSK, WIFI_AUTH_WPA2_PSK, WIFI_AUTH_WPA3_PSK
#define AP_CHANNEL    6                    // Wi-Fi channel (1-14)
#define AP_MAX_CONN   5                    // Max clients

static const char *TAG = "wifi_softAP";

void wifi_init_softap(void) {
    wifi_config_t wifi_config = {
        .ap = {
            .ssid = AP_SSID,
            .ssid_len = strlen(AP_SSID),
            .channel = AP_CHANNEL,
            .password = AP_PASSWORD,
            .max_connection = AP_MAX_CONN,
            .authmode = AP_SECURITY_MODE,
        },
    };

    // Enable PMF (Required for WPA3)
    if (AP_SECURITY_MODE == WIFI_AUTH_WPA3_PSK) {
        wifi_config.ap.pmf_cfg.required = true;
    }

    // Initialize Wi-Fi
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "AP started: SSID=%s, Security=%d", AP_SSID, AP_SECURITY_MODE);
}

void app_main() {
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Initialize Wi-Fi stack
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    // Start AP
    wifi_init_softap();
}
