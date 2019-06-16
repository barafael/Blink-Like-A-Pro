for i in range(1, 2**16):
  peri = 8000000 / i;
  if peri > 2**16 - 1:
    continue;
  if peri.is_integer():
    print(peri, i)


