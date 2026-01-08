# STM32 JSON Serializer (Embedded Firmware)

## Overview
This project implements an embedded-friendly JSON serialization library in C.  
It converts structured smart-meter data into a fixed, predefined JSON format suitable for gateway or backend integration.

w-M-Bus communication, OMS handling, encryption, and real meter interaction are intentionally out of scope.

---

## Platform and Language
Platform: STM32 (STM32CubeIDE)  
Programming Language: C

C was chosen for its low overhead, deterministic behavior, and precise memory control, which are essential for embedded firmware development.

---

## Project Structure
Inc/  
- data_model.h – internal data structures  
- json_serializer.h – public serialization API  

Src/  
- json_serializer.c – JSON serialization logic  
- main.c – demo / example application  

---

## Public API
The library exposes a single function to serialize data into JSON:

serialize_to_json(payload, output_buffer, buffer_size, output_length)

The caller provides the output buffer.  
The function returns explicit status codes to indicate success or failure.

---

## JSON Output
The generated JSON strictly follows the format defined in the assignment:
- Field names and structure are unchanged
- Numeric values are serialized as numbers
- The outer JSON element is always an array
- No additional fields are added

---

## Demo Application
A demo application is included in main.c.  
It creates sample input data, calls the serialization function, and prints the generated JSON using printf.

The demo is transport-agnostic and does not rely on UART, radio, or networking.

---

## Embedded Design Considerations
- No dynamic memory allocation
- Caller-owned output buffers
- Safe string handling with buffer size checks
- Explicit error handling
- Transport-agnostic core logic

---

## Build Instructions
Open the project in STM32CubeIDE and build it.  
No hardware connection is required.

---

## Notes
This project demonstrates a realistic embedded firmware task focused on clean architecture, deterministic memory usage, and reliable data serialization.
