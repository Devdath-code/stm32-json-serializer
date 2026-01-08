#include "json_serializer.h"
#include <stdio.h>   // for snprintf

/* Helper macro to safely append formatted text to buffer */
#define APPEND(fmt, ...)                                      \
    do {                                                      \
        int written = snprintf(out_buf + idx,                 \
                               buf_size - idx,               \
                               fmt, ##__VA_ARGS__);           \
        if (written < 0 || (size_t)written >= buf_size - idx) \
            return JSON_BUFFER_TOO_SMALL;                     \
        idx += written;                                      \
    } while (0)

JsonStatus serialize_to_json(
    const Payload *payload,
    char *out_buf,
    size_t buf_size,
    size_t *out_len
) {
    size_t idx = 0;

    /* Basic input validation */
    if (!payload || !out_buf) {
        return JSON_INVALID_INPUT;
    }

    /* Start JSON array and object */
    APPEND("[{");

    /* Gateway metadata */
    APPEND("\"gatewayId\":\"%s\",", payload->meta.gatewayId);
    APPEND("\"date\":\"%s\",", payload->meta.date);
    APPEND("\"deviceType\":\"%s\",", payload->meta.deviceType);
    APPEND("\"interval_minutes\":%d,", payload->meta.interval_minutes);
    APPEND("\"total_readings\":%d,", payload->meta.total_readings);

    /* Values section */
    APPEND("\"values\":{");
    APPEND("\"device_count\":%d,", payload->values.device_count);
    APPEND("\"readings\":[");

    /* Loop over devices */
    for (int i = 0; i < payload->values.device_count; i++) {
        DeviceReading *r = &payload->values.readings[i];

        APPEND("{");
        APPEND("\"media\":\"%s\",", r->media);
        APPEND("\"meter\":\"%s\",", r->meter);
        APPEND("\"deviceId\":\"%s\",", r->deviceId);
        APPEND("\"unit\":\"%s\",", r->unit);
        APPEND("\"data\":[");

        /* Loop over data points */
        for (int j = 0; j < r->data_count; j++) {
            DataPoint *d = &r->data[j];

            APPEND("{");
            APPEND("\"timestamp\":\"%s\",", d->timestamp);
            APPEND("\"meter_datetime\":\"%s\",", d->meter_datetime);
            APPEND("\"total_m3\":%.3f,", d->total_m3);
            APPEND("\"status\":\"%s\"", d->status);
            APPEND("}");

            if (j < r->data_count - 1) {
                APPEND(",");
            }
        }

        APPEND("]}");

        if (i < payload->values.device_count - 1) {
            APPEND(",");
        }
    }

    /* Close JSON */
    APPEND("]}");
    APPEND("}]");

    if (out_len) {
        *out_len = idx;
    }

    return JSON_OK;
}
