# Notizen

## Idee

- QRCode
- Jumper der zwischen Buttons und Fototransistor wechselt
    - Fototransistor kann dann genutzt werden, um die Zeit von einer Webseite per Flickercode zu übertragen
- vllt Transistor woanders dran machen (Matrix oder I2C)

## Software
- https://forum.arduino.cc/t/time-libary-sommerzeit-winterzeit/221884


## ADC Calculation
| No. Switches    |           3 |        | Button No. | Req'd ADC | Req'd V (R1) | Req'd V (R2+) | Req'd R | Closest R | Actual V (R1) | Actual V (R2+) | Actual ADC | Diff from prev. | In Tolerance | Current (mA) |
|-----------------|------------:|--------|-----------:|----------:|-------------:|--------------:|--------:|----------:|--------------:|---------------:|-----------:|----------------:|-------------:|-------------:|
| ADC Resolution  |        1024 |        |          0 |      1024 |         0.00 |          5.00 |   47000 |     47000 |          5.00 |           0.00 |          0 |               0 |          N/A |         0.11 |
| Tolerance (%)   |           2 |        |          1 |       341 |         3.33 |          1.67 |   23500 |     24000 |          3.31 |           1.69 |        346 |             346 |          YES |         0.07 |
| Voltage         |           5 |        |          2 |       683 |         1.67 |          3.33 |   70500 |     68000 |          1.69 |           3.31 |        678 |             332 |          YES |         0.04 |
|                 |             |        |          3 |           |              |               |         |           |               |                |            |                 |              |              |
|                 |             |        |          4 |           |              |               |         |           |               |                |            |                 |              |              |
|                 |             |        |          5 |           |              |               |         |           |               |                |            |                 |              |              |
|                 |             |        |          6 |           |              |               |         |           |               |                |            |                 |              |              |
|                 |             |        |          7 |           |              |               |         |           |               |                |            |                 |              |              |
| ADC Tolerance   |       20.48 |  (+/-) |          8 |           |              |               |         |           |               |                |            |                 |              |              |
| Std. Deviation  | 10.27164132 |        |          9 |           |              |               |         |           |               |                |            |                 |              |              |
|                 |             |        |         10 |           |              |               |         |           |               |                |            |                 |              |              |
|                 |             |        |         11 |           |              |               |         |           |               |                |            |                 |              |              |