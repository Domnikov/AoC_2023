#pragma once
#include "../help_func.hpp"

inline auto getInput()
{
    VECS input {
"#.#####################",
"#.......#########...###",
"#######.#########.#.###",
"###.....#.>.>.###.#.###",
"###v#####.#v#.###.#.###",
"###.>...#.#.#.....#...#",
"###v###.#.#.#########.#",
"###...#.#.#.......#...#",
"#####.#.#.#######.#.###",
"#.....#.#.#.......#...#",
"#.#####.#.#.#########v#",
"#.#...#...#...###...>.#",
"#.#.#v#######v###.###v#",
"#...#.>.#...>.>.#.###.#",
"#####v#.#.###v#.#.###.#",
"#.....#...#...#.#.#...#",
"#.#########.###.#.#.###",
"#...###...#...#...#.###",
"###.###.#.###v#####v###",
"#...#...#.#.>.>.#.>.###",
"#.###.###.#.###.#.#v###",
"#.....###...###...#...#",
"#####################.#",
    };

    return input;
}
