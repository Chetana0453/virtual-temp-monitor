# Testing and Results
nano docs/testing.md
## 1. Test Environment
- Date: 2 October 2026
- Operating system: Ubuntu on WSL2
- Kernel: 6.6.87.2-microsoft-standard-WSL2
- Device: /dev/vtemp
- Application: app/monitor

## 2. Test Method
Tests were performed manually using Ubuntu terminal commands.
Valid and invalid values were written to the device, and the
C++ application was used to check the stored temperature.

## 3. Test Results

### T01 — Minimum Temperature
- Input: -40
- Expected: Accept the value.
- Actual: Application displayed -40 C.
- Status: PASS

### T02 — Maximum Temperature
- Input: 125
- Expected: Accept the value.
- Actual: Application displayed 125 C.
- Status: PASS

### T03 — Above Maximum
- Input: 126
- Expected: Reject the value and keep 125 C.
- Actual: Error reported; temperature stayed at 125 C.
- Status: PASS

### T04 — Below Minimum
- Input: -41
- Expected: Reject the value and keep the previous temperature.
- Actual: Error reported, temperature stayed at 125 C.
- Status: PASS.

### T05 — Non-Numeric Input
- Input: abc
- Expected: Reject the text and keep the previous temperature.
- Actual: Error reported, temperature stayed at 125 C.
- Status: PASS.

### T06 — Oversized Input
- Input: 12345678901234567890
- Expected: Reject the input and keep 125 C.
- Actual: Error reported; temperature stayed at 125 C.
- Status: PASS

### T07 — Driver Unavailable
- Action: Unload the driver and run the application.
- Expected: Missing-device error and exit status 1.
- Actual: Missing-device error and exit status 1 confirmed.
- Status: PASS

### T08 — Reload Driver
- Action: Load the driver again and read the temperature.
- Expected: Temperature resets to 25 C.
- Actual: Application displayed 25 C.
- Status: PASS

### T09 — Access Without Permission
- Action: Run the application without sudo.
- Expected: Permission-denied error and exit status 1.
- Actual: Permission-denied error confirmed; exit status 1 confirmed earlier.
- Status: PASS.

## 4. Meaning of Expected Errors
An error during an invalid-write test is the expected behaviour.
It shows that the driver rejected the input.

A complete invalid-write test also checks that the previously
stored temperature remains unchanged.

Application exit status 0 indicates success.
Application exit status 1 indicates an error.

## 5. Remaining Checks
- Test concurrent reads and writes.
- Inspect kernel messages after concurrent testing.

## 6. Test Limitations
These results cover the manual tests listed above.
They do not prove that every possible input or concurrency scenario is handled correctly.
