(* lab 1 *)
fun sum [ ] = 0
    | sum (x ::L) = x + (sum L);

fun mult [ ] = 1	
    | mult (x ::L) = x * (mult L);

fun Mult [ ] = 1	
    | Mult (r :: R) = mult(r) * Mult(R);	

fun mult' ([ ], a) = a
    | mult' (x :: L, a) = mult' (L, x * a);

fun Mult' ( [ ], a) = a	
    | Mult' (r::R, a) = Mult'(R, mult'(r, a));	

fun double (0 : int) : int = 0
    | double n = 2 + double (n - 1);

fun square (0 : int) : int = 0
    | square n = (square (n - 1)) + double(n) - 1;

fun divisibleByThree(0 : int) : bool = true
    | divisibleByThree 1 = false
    | divisibleByThree 2 = false
    | divisibleByThree n = divisibleByThree(n - 3);

fun evenP (0 : int) : bool = true
    | evenP 1 = false
    | evenP n = evenP (n - 2);

fun oddP (0 : int) : bool = false
    | oddP 1 = true
    | oddP n = oddP (n - 2);

(* lab 2 *)
fun reverse []:int list = []
    | reverse(x::L):int list = reverse(L)@[x];

fun reverse' (L:int list):int list =
    let
        fun Reverse(L,OUT)=
            case L of
                [] =>OUT
                | x::last => Reverse(last,x::OUT)
    in
        Reverse(L,[])
end    

fun interleave([],[]) : int list = []
    | interleave([],R) : int list = R
    | interleave(L,[]) :int list = L
    | interleave(x::L,y::R) : int list = x::y::interleave(L,R);

fun split ([]) : (int list * int * int list)  = raise Fail "split on an empty list"
    | split (L:int list) : (int list * int * int list) =
	    let 
            val m = (length L) div 2
            val l = List.take(L,m)
            val x::r = List.drop(L,m)
	    in 
            (l,x,r)	
end

(* datatype tree = Empty | Node of tree * int * tree *)
datatype 'a tree = Empty | Node of 'a tree * 'a * 'a tree

fun listToTree ([]) : int tree = Empty
  | listToTree (L) : int tree =
    let
      val (l, x, r) = split L
    in
      Node (listToTree l, x , listToTree r)
end

fun revT (Empty : int tree) = Empty
    | revT (Node(l,x,r)) = Node(revT r,x,revT l);

fun trav Empty = [] 
    | trav (Node(t1, x, t2)) = trav t1 @ (x :: trav t2);

fun sorted [ ] = true
	| sorted [x] = true
	| sorted (x::y::L) =
	   (case Int.compare(x,y) of
      GREATER => false
      |EQUAL => sorted(y::L)
      |LESS =>sorted(y::L))

fun binarySearch (Empty : int tree, x : int) : bool = false
    | binarySearch( (Node(l,x,r)) , y:int) : bool = 
      if sorted(trav(Node(l,x,r))) then 
        (case Int.compare(x,y) of
            GREATER => binarySearch(l,y)
            |EQUAL => true
            |LESS => binarySearch(r,y))
      else
        raise Fail "this is not a sorted list"  

(* lab 3 *)
fun factorial(0 : int) = 1
    | factorial n = n * factorial (n-1);

fun thenAddOne (f , x :int) :int = f(x) + 1;

fun mapList (f: 'a -> 'b, [] : 'a list): 'b list = []
  | mapList (f  , x::L ) = (f x)::mapList(f, L)

fun mapList' (f: 'a -> 'b)(L) = mapList(f,L);

fun findOdd [] : int option = NONE
    |findOdd (x::L) = 
        if oddP(x) then SOME x
        else
            findOdd(L)

fun zero(0:int) : bool = true
  | zero (x:int) :bool = false

fun subsetSumOption ([] : int list, _) :int list option = NONE
    | subsetSumOption (x::L,s) = 
      if zero(s-x) then 
        SOME [x]
      else
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