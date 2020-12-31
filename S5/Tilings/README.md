# TILINGS

<https://www.labri.fr/perso/renault/working/teaching/projets/2020-21-S5-Tilings.php>

To read the project documentation: `doc/index.html`

## Usage

- Compilation: `make` 
- Run : `./project`

 ### Optional parameters

- `-o` : parameter to see the execution of the program (small board recommended)

- `-n`:  parameter for the number of players

- `-s`:  parameter to initialize the RNG

- `-b`: parameter for the size of the board

## Convention

### Code style

The formatting of the code follows the principles of the [LLVM Coding Standards](https://llvm.org/docs/CodingStandards.html). All rules are defined at the root of the project in the `.clang-format file`, and formatting can be done automatically by the command `./format_sources.sh`

### Documentation style

For the code documentation, we use the [Dyoxygen](https://www.doxygen.nl/) tool (`make doc` for the generation). The commenting convention will therefore follow the following formats:

```c
/***************************************************************************//**
 * A brief history of Doxygen-style banner comments.
 *
 * This is a Doxygen-style C-style "banner" comment. It starts with a "normal"
 * comment and is then converted to a "special" comment block near the end of
 * the first line. It is written this way to be more "visible" to developers
 * who are reading the source code.
 * This style of commenting behaves poorly with clang-format.
 *
 * @param theory Even if there is only one possible unified theory. it is just a
 *               set of rules and equations. (optional)
 * @return Describe here what the function returns (optional)
 ******************************************************************************/
int doxygenBanner( int theory );
```

```c
int var; /**< Detailed description after the member */
```

## Authors

- [Waris Radji](https://warisradji.com/)
- Marwan Zizi

## Dépôt pour les projets S5 (PR103)

- Lien vers le sujet du projet :

	<https://www.labri.fr/perso/renault/working/teaching/projets/2020-21-S5-Tilings.php>

- Lien vers le projet sur la forge :

	<https://thor.enseirb-matmeca.fr/ruby/projects/projetss5>

- Lien vers la documentation sur l'utilisation de git :

	<https://thor.enseirb-matmeca.fr/ruby/docs/repository/git>
