checkPrimes <- function(numbers)
{
  result <- sapply(numbers, isPrime)
  return(result)
}