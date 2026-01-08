#ifndef DATA_MODEL_H
#define DATA_MODEL_H

/*Gateway metadata*/
typedef struct {
    const char *gatewayId;
    const char *date;              // YYYY-MM-DD
    const char *deviceType;
    int interval_minutes;
    int total_readings;
} GatewayMeta;

/*Single data point */
typedef struct {
    const char *timestamp;
    const char *meter_datetime;
    float total_m3;
    const char *status;
} DataPoint;

/*Device reading*/
typedef struct {
    const char *media;
    const char *meter;
    const char *deviceId;
    const char *unit;

    DataPoint *data;
    int data_count;
} DeviceReading;

/*Values wrapper*/
typedef struct {
    int device_count;
    DeviceReading *readings;
} Values;

/*Full payload*/
typedef struct {
    GatewayMeta meta;
    Values values;
} Payload;

#endif /* DATA_MODEL_H */
