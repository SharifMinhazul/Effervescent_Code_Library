>[First Write a Brute Force solution]
>Nim = all xor
>Misere Nim = Nim + corner case: if all piles are 1, reverse(nim)
>Bogus Nim = Nim
>Staircase Nim = Odd indexed pile Nim (Even indexed pile doesnt matter, as one player can give bogus moves to drop all even piles to ground)
>Sprague Grundy: [Every impartial game under the normal play convention is equivalent to a one-heap game of nim] 
Every tree = one nim pile = tree root value; tree leaf value = 0; tree node value = mex of all child nodes.
[Careful: one tree node can become multiple new tree roots(multiple elements in one node), then the value of that node = xor of all those root values]
>Hackenbush(Given a rooted tree; cut an edge in one move; subtree under that edge gets removed; last player to cut wins): 
Colon: //$G(u) = (G(v1)+1) \oplus (G(v2)+1) \oplus \cdots [v1, v2,\cdots$ are childs of u]
For multiple trees ans is their xor
>Hackenbush on graph (instead of tree given an rooted graph): 
fusion: All edges in a cycle can be fused to get a tree structure; build a super node, connect some single nodes with that super node, number of single nodes is the number of edges in the cycle.
Sol: [Bridge component tree] mark all bridges, a group of edges that are not bridges, becomes one component and contributes number of edges to the hackenbush. (even number of edges contributes 0, odd number of edges contributes 1)
