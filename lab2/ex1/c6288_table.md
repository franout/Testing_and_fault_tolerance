## PO masks to the C6288 circuit

| PO mask | test patterns | test coverage | non controlled faults | not observed faults |
| --------|--------------|---------------|-----------------------|----------------------|
| none | 59 | 99.88 % | 68 | 17 |
| datao(1) | 59  | 99.83 % | 68 | 17 |
| datao(2) | 59 | 99.72 % | 68 | 20 |
| datao(3) | 59 | 99.71 % | 68 | 22 |
| datao(0) to datao(3) | 59 | 99.18 % | 68 | 17 |
|All but datao(1) to datao(3) | 59 | 29.39 % | 69 | 9671 |
| All | 59 | 0.00 % | 69 | 6304 |
