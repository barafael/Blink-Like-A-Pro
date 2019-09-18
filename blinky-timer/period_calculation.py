sysClock = 8000000
for i in range(1, 2**16):
  period = sysClock / i;
  if period > 2**16 - 1:
    continue;
  if period.is_integer():
    print(period, i)
