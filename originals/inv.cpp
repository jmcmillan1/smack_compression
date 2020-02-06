template<typename T>
static size_t INV(T *const in, const size_t len, T *const out)
{
  for (size_t pos = 0; pos < len; pos++) {
    out[pos] = ~in[pos];
  }
  return len;
}

template<typename T>
static size_t iINV(T *const in, const size_t len, T *const out)
{
  return INV(in, len, out);
}
