# Advent of code 2021
These are my sollutions to AoC 2021.
### language used ```C```
___
In these sollutions I'll be trying to get better at using ```C```  by trying different standard functions and attempting to write my own parsing functions.


### Hi there,
___
This is my first year participating in this event.
So I don't know if I can finnish all puzzles on time, or at all...

But i'll be trying my best to keep up.

The solutions are probably a bit hacky.

## benchmarks:
Benchmarks are ran with hyperfine

| Command | Mean [ms] | Min [ms] | Max [ms] | Result |
|:---|---:|---:|---:|---:|
| `./01/star1 < 01/Input.txt` | 4.0 ± 0.3 | 3.6 | 7.1 | ⭐ |
| `./01/star2 < 01/Input.txt` | 4.0 ± 0.3 | 3.5 | 6.4 | ⭐ |
| `./02/star1 < 02/Input.txt` | 3.8 ± 0.2 | 3.4 | 4.7 | ⭐ |
| `./02/star2 < 02/Input.txt` | 3.8 ± 0.3 | 3.4 | 6.7 | ⭐ |
| `./03/star1 < 03/Input.txt` | 4.1 ± 0.2 | 3.7 | 4.8 | ⭐ |
| `./03/star2 < 03/Input.txt` | 4.2 ± 0.3 | 3.7 | 7.1 | ⭐ |
| `./04/star1 < 04/Input.txt` | 4.4 ± 0.5 | 3.6 | 7.7 | ⭐ |
| `./04/star2 < 04/Input.txt` | 4.6 ± 0.3 | 4.2 | 7.5 | ⭐ |
| `./05/star1 < 05/Input.txt` | 7.6 ± 0.3 | 7.1 | 8.5 | ⭐ |
| `./05/star2 < 05/Input.txt` | 7.7 ± 0.3 | 7.1 | 8.6 | ⭐ |
| `./06/star1 < 06/Input.txt` | 41.6 ± 1.3 | 40.5 | 49.0 |⭐ |
| `./06/star2 < 06/Input.txt` | 3.5 ± 0.2 | 3.0 | 5.1 | ⭐ |
| `./07/star1 < 07/Input.txt` | 3.6 ± 0.3 | 3.2 | 7.5 | ⭐ |
| `./07/star2 < 07/Input.txt` | 3.8 ± 0.3 | 3.2 | 7.1 | ⭐ |
| `./08/star1 < 08/Input.txt` | 4.5 ± 0.2 | 3.9 | 5.3 | ⭐ |
| `./08/star2 < 08/Input.txt` | 4.8 ± 0.3 | 4.3 | 7.4 | ⭐ |
| `./09/star1 < 09/Input.txt` | 4.6 ± 0.3 | 4.2 | 5.5 | ⭐ |
| `./09/star2 < 09/Input.txt` | 5.1 ± 0.3 | 4.7 | 9.0 | ⭐ |
| `./10/star1 < 10/Input.txt` | 4.2 ± 0.3 | 3.7 | 5.0 | ⭐ |
| `./10/star2 < 10/Input.txt` | 4.4 ± 0.3 | 3.9 | 7.5 | ⭐ |
| `./11/star1 < 11/Input.txt` | 4.1 ± 0.3 | 3.5 | 5.2 | ⭐ |
| `./11/star2 < 11/Input.txt` | 4.6 ± 0.4 | 4.0 | 8.5 | ⭐ |
| `./12/star1 < 12/Input.txt` | 5.3 ± 0.3 | 4.9 | 6.6 | ⭐ |
| `./12/star2 < 12/Input.txt` | 19.1 ± 0.6 | 18.5 | 25.4 | ⭐ |