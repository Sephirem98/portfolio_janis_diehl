// Author: Janis Diehl
// Created:October 2024
// Purpose: Solving the code.golf exercise Diamonds in brainfuck with as little characters as possible
// Problems: Optimization for minimal characterlimit leads to lack of readability

// Cell 1 is set to value 10 for ASCII linebreaks.
// Cell 2 is set to value 32 for ASCII spaces.
// Cell 3 is initially set to value 48 for ASCII '0'. This will be the output cell.
// Cell 4 is initially set to value 9 for the amount of diamonds to be produced.
// Cell 5 is initially set to value 1. This Cell dictates the amount of lines for each diamond and will increment with each new diamond.
// Cell 6 is initially set to value 9. This Cell dictates the amount of spaces between line start and the first numeric character in each line.
// Cell 7 acts as a counterweight for Cell 6 and will decrease by one for each line in a diamond. At the start of a new diamond this will be reset.
// Cell 8 dictates the amount of numeric characters per line.
// Cell 9 acts as a counterweight for Cell 8.
++++++++++[
	->+>+++>+++++>+<<<<
]
>>++>-->->+<[
	->>+++++++++<[
		->[
			-<<<<.>>>>>+<
		]
		>-[
			-<+>
		]
		>+[
			-<<<<<+.>>>>>>+<
		]
		>-[
			-<+<<<<<-.>>>>>>
		]
		<+<<<<<-<<.<+>>>>>
	]
	>++>>-<<<<<<<<-[
		->>>>>>[
			-<<<<.>>>>>+<
		]
		>+[
			-<+>
		]
		>[
			-<<<<<+.>>>>>>+<
		]
		>-[
			-<+<<<<<-.>>>>>>
		]
		<<<<+<<-<<.<
	]
	>.>>>>++>[
		-
	]
	<<
]