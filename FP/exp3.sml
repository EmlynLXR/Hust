fun thenAddOne (f , x :int) :int = f(x) + 1;

fun double (0 : int) : int = 0
    | double n = 2 + double (n - 1);

fun square (0 : int) = 0
    | square n = (square (n - 1)) + (double n) - 1;

fun oddP (0 : int) : bool = false
    | oddP 1 = true
    | oddP n = oddP (n - 2);

datatype 'a tree = Empty
                 | Node of 'a tree * 'a * 'a tree

fun factorial(0 : int) = 1
    | factorial n = n * factorial (n-1);

fun mapList (f: 'a -> 'b, [] : 'a list): 'b list = []
  | mapList (f  , x::L ) = (f x)::mapList(f, L)

fun mapList' (f: 'a -> 'b)(L) = mapList(f,L);


fun findOdd [] : int option = NONE
    |findOdd (x::L) = 
        if oddP(x) then SOME x
        else
            findOdd(L)

fun subsetSumOption ([] : int list, _) :int list option = NONE
    | subsetSumOption (L : int list, 0 : int) :int list option = SOME []
    | subsetSumOption (x::L,s) = 
        case subsetSumOption(L,s-x) of
            SOME (l) => SOME (x::l)
            |NONE => subsetSumOption(L,s)

fun exists(f:'a -> bool)([] : 'a list) :bool = false
    |exists(f:'a -> bool)(x::L) = 
        if f(x) then
            true
        else
            exists(f)(L)

fun forall(f:'a -> bool)([] : 'a list) :bool = true
    |forall(f:'a -> bool)(x::L) = 
        if f(x) then
            forall(f)(L)
        else
            false

fun treeFilter (f: 'a -> bool)(Empty) : 'a option tree = Empty
    |treeFilter (f: 'a -> bool)(Node(l,x,r)) : 'a option tree =
    let
      val root = 
        if f(x) then 
            SOME x 
        else 
            NONE
    in
      Node (treeFilter f(l), root, treeFilter (f)(r))
    end        
