#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include <stddef.h>     // for size_t
#include "data_model.h"

/* Error codes returned by the serializer*/
typedef enum {
    JSON_OK = 0,
    JSON_BUFFER_TOO_SMALL,
    JSON_INVALID_INPUT
} JsonStatus;

/*
 * Serialize payload data into JSON.
 *
 * payload : input data (must not be NULL)
 * out_buf : output buffer provided by caller
 * buf_size : size of output buffer
 * out_len : number of bytes written (can be NULL)
 *
 * Returns JsonStatus
 */
JsonStatus serialize_to_json(
    const Payload *payload,
    char *out_buf,
    size_t buf_size,
    size_t *out_len
);

#endif /* JSON_SERIALIZER_H */
