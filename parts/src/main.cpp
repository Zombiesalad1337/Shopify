digraph "Project" {
node [
  fontsize = "12"
];
subgraph clusterLegend {
  label = "Legend";
  color = black;
  edge [ style = invis ];
  legendNode0 [ label = "Executable", shape = egg ];
  legendNode1 [ label = "Static Library", shape = octagon ];
  legendNode2 [ label = "Shared Library", shape = doubleoctagon ];
  legendNode3 [ label = "Module Library", shape = tripleoctagon ];
  legendNode4 [ label = "Interface Library", shape = pentagon ];
  legendNode5 [ label = "Object Library", shape = hexagon ];
  legendNode6 [ label = "Unknown Library", shape = septagon ];
  legendNode7 [ label = "Custom Target", shape = box ];
  legendNode0 -> legendNode1 [ style = solid ];
  legendNode0 -> legendNode2 [ style = solid ];
  legendNode0 -> legendNode3;
  legendNode1 -> legendNode4 [ label = "Interface", style = dashed ];
  legendNode2 -> legendNode5 [ label = "Private", style = dotted ];
  legendNode3 -> legendNode6 [ style = solid ];
  legendNode0 -> legendNode7;
}
    "node0" [ label = "inventory", shape = doubleoctagon ];
    "node1" [ label = "item", shape = doubleoctagon ];
    "node2" [ label = "main", shape = egg ];
    "node2" -> "node0" [ style = dotted ] // main -> inventory
    "node2" -> "node1" [ style = dotted ] // main -> item
    "node3" [ label = "map", shape = doubleoctagon ];
    "node4" [ label = "polygon", shape = doubleoctagon ];
    "node3" -> "node4"  // map -> polygon
    "node5" [ label = "vertex", shape = doubleoctagon ];
    "node3" -> "node5"  // map -> vertex
    "node2" -> "node3" [ style = dotted ] // main -> map
    "node6" [ label = "userlist", shape = doubleoctagon ];
    "node2" -> "node6" [ style = dotted ] // main -> userlist
    "node7" [ label = "utils", shape = doubleoctagon ];
    "node2" -> "node7" [ style = dotted ] // main -> utils
}
