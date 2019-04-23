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

datatype tree = Empty | Node of tree * int * tree

fun listToTree ([]) : tree = Empty
  | listToTree (L) : tree =
    let
      val (l, x, r) = split L
    in
      Node (listToTree l, x , listToTree r)
end

fun revT (Empty : tree) = Empty
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

fun binarySearch (Empty : tree, x : int) : bool = false
    | binarySearch( (Node(l,x,r)) , y:int) : bool = 
      if sorted(trav(Node(l,x,r))) then 
        (case Int.compare(x,y) of
            GREATER => binarySearch(l,y)
            |EQUAL => true
            |LESS => binarySearch(r,y))
      else
        raise Fail "this is not a sorted list"  