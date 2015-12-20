stringToCharList :: String -> String
stringToCharList [] = []
stringToCharList (a:as) = a : "','" ++ stringToCharList as

strC :: String -> String
strC s = "{'" ++ take (length t - 2) t ++  "}"
  where t = stringToCharList s