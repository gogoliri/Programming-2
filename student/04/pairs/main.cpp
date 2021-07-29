/* Pairs
 *
 * Desc:
 *  This program generates a pairs (memory) game. The game has a variant
 * number of cards and players. At the beginning, the program also asks for a
 * seed value, since the cards will be set randomly in the game board.
 *  On each round, the player in turn gives the coordinates of two cards
 * (totally four numbers). After that the given cards will be turned as
 * visible and told if they are pairs or not. If they are pairs, they are
 * removed from the game board, the score of the player is increased, and
 * a new turn is given for the player. If the cards are not pairs, they
 * will be  turned hidden again, and the next player will be in turn.
 *  The program checks if the user-given coordinates are legal. The cards
 * determined by the coordinates must be found in the game board.
 *  After each change, the game board is printed again. The cards are
 * described as letters, starting from A and lasting so far as there are
 * cards. In printing the game board, a visible card is shown as its letter,
 * a hidden one as the number sign (#), and a removed one as a dot.
 *  Game will end when all pairs have been found, and the game board is
 * empty. The program tells who has/have won, i.e. collected most pairs.
 */
 /* Program author
 * Name: Khoa Pham Dinh
 * Student number: 050359620
 * UserID: gmkhph
 * E-Mail: khoa.phamdinh@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 * */

#include <player.hh>
#include <card.hh>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

const string INPUT_AMOUNT_OF_CARDS = "Enter the amount of cards (an even number): ";
const string INPUT_SEED = "Enter a seed value: ";
const string INPUT_AMOUNT_OF_PLAYERS = "Enter the amount of players (one or more): ";
const string INPUT_CARDS = "Enter two cards (x1, y1, x2, y2), or q to quit: ";
const string INVALID_CARD = "Invalid card.";
const string FOUND = "Pairs found.";
const string NOT_FOUND = "Pairs not found.";
const string GIVING_UP = "Why on earth you are giving up the game?";
const string GAME_OVER = "Game over!";

using Game_row_type = vector<Card>;
using Game_board_type = vector<vector<Card>>;

// Muuntaa annetun numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota).
// Jos annettu merkkijono ei ole numeerinen, palauttaa nollan
// (mikä johtaa laittomaan korttiin myöhemmin).
//
// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns 0
// (which leads to an invalid card later).
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

// Täyttää pelilaudan (kooltaan rows * columns) tyhjillä korteilla.
//
// Fills the game board, the size of which is rows * columns, with empty cards.
void init_with_empties(Game_board_type& g_board, unsigned int rows, unsigned int columns)
{
    g_board.clear();
    Game_row_type row;
    for(unsigned int i = 0; i < columns; ++i)
    {
        Card card;
        row.push_back(card);
    }
    for(unsigned int i = 0; i < rows; ++i)
    {
        g_board.push_back(row);
    }
}

// Etsii seuraavan tyhjän kohdan pelilaudalta (g_board) aloittamalla
// annetusta kohdasta start ja jatkamalla tarvittaessa alusta.
// (Kutsutaan vain funktiosta init_with_cards.)
//
// Finds the next free position in the game board (g_board), starting from the
// given position start and continuing from the beginning if needed.
// (Called only by the function init_with_cards.)
unsigned int next_free(Game_board_type& g_board, unsigned int start)
{
    // Selvitetään annetun pelilaudan rivien ja sarakkeiden määrät
    //
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    // Aloitetaan annetusta arvosta
    //
    // Starting from the given value
    for(unsigned int i = start; i < rows * columns; ++i)
    {
        if(g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY) // vaihdettu
        {
            return i;
        }
    }
    // Jatketaan alusta
    //
    // Continuing from the beginning
    for(unsigned int i = 0; i < start; ++i)
    {
        if(g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY)
        {
            return i;
        }
    }
    // Tänne ei pitäisi koskaan päätyä
    //
    // You should never reach this
    std::cout << "No more empty spaces" << std::endl;
    return rows * columns - 1;
}

// Alustaa annetun pelilaudan (g_board) satunnaisesti arvotuilla korteilla
// annetun siemenarvon (seed) perusteella.
//
// Initializes the given game board (g_board) with randomly generated cards,
// based on the given seed value.
void init_with_cards(Game_board_type& g_board, int seed)
{
    // Selvitetään annetun pelilaudan rivien ja sarakkeiden määrät
    //
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    // Arvotaan täytettävä sijainti
    //
    // Drawing a cell to be filled
    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distr(0, rows * columns - 1);
    // Hylätään ensimmäinen satunnaisluku (joka on aina jakauman alaraja)
    //
    // Wiping out the first random number (that is always the lower bound of the distribution)
    distr(randomEng);

    // Jos arvotussa sijainnissa on jo kortti, valitaan siitä seuraava tyhjä paikka.
    // (Seuraava tyhjä paikka haetaan kierteisesti funktion next_free avulla.)
    //
    // If the drawn cell is already filled with a card, next empty cell will be used.
    // (The next empty cell is searched for circularly, see function next_free.)
    for(unsigned int i = 0, c = 'A'; i < rows * columns - 1; i += 2, ++c)
    {
        // Lisätään kaksi samaa korttia (parit) pelilaudalle
        //
        // Adding two identical cards (pairs) in the game board
        for(unsigned int j = 0; j < 2; ++j)
        {
            unsigned int cell = distr(randomEng);
            cell = next_free(g_board, cell);
            g_board.at(cell / columns).at(cell % columns).set_letter(c);
            g_board.at(cell / columns).at(cell % columns).set_visibility(HIDDEN);
        }
    }
}

// Tulostaa annetusta merkistä c koostuvan rivin,
// jonka pituus annetaan parametrissa line_length.
// (Kutsutaan vain funktiosta print.)
//
// Prints a line consisting of the given character c.
// The length of the line is given in the parameter line_length.
// (Called only by the function print.)
void print_line_with_char(char c, unsigned int line_length)
{
    for(unsigned int i = 0; i < line_length * 2 + 7; ++i)
    {
        cout << c;
    }
    cout << endl;
}

// Tulostaa vaihtelevankokoisen pelilaudan reunuksineen.
//
// Prints a variable-length game board with borders.
void print(const Game_board_type& g_board)
{
    // Selvitetään annetun pelilaudan rivien ja sarakkeiden määrät
    //
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    print_line_with_char('=', columns);
    cout << "|   | ";
    for(unsigned int i = 0; i < columns; ++i)
    {
        cout << i + 1 << " ";
    }
    cout << "|" << endl;
    print_line_with_char('-', columns);
    for(unsigned int i = 0; i < rows; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < columns; ++j)
        {
            g_board.at(i).at(j).print();
            cout << " ";
        }
        cout << "|" << endl;
    }
    print_line_with_char('=', columns);
}

// Kysyy käyttäjältä tulon ja sellaiset tulon tekijät, jotka ovat
// mahdollisimman lähellä toisiaan.
//
// Asks the desired product from the user, and calculates the factors of
// the product such that the factor as near to each other as possible.
void ask_product_and_calculate_factors(unsigned int& smaller_factor,
                                       unsigned int& bigger_factor)
{
    unsigned int product = 0;
    while(not (product > 0 and product % 2 == 0))
    {
        std::cout << INPUT_AMOUNT_OF_CARDS;
        string product_str = "";
        std::getline(std::cin, product_str);
        product = stoi_with_check(product_str);
    }

    for(unsigned int i = 1; i * i <= product; ++i)
    {
        if(product % i == 0)
        {
            smaller_factor = i;
        }
    }
    bigger_factor = product / smaller_factor;
}

// Lisää funktioita
// More functions

//Define list of players as a type
//For increasing of clarification
using Player_list_type = vector<Player>;

void Ask_number_of_players
    (Player_list_type& player_list){

    string number_of_player_input;// input from keyboard
    unsigned int number_of_player = 0;// the number after conveting

    while(number_of_player == 0){
        std::cout << INPUT_AMOUNT_OF_PLAYERS;
        cin>> number_of_player_input;

        number_of_player = stoi_with_check(number_of_player_input);
    }

    std::cout<<"List "<<number_of_player<<" players: ";
    for(unsigned int i = 0; i < number_of_player;i++){
        std::string player_name;
        cin>>player_name;
        player_list.push_back(player_name);
    }
}

// Validity type to make 3 state of the ouput when coordinators given
enum Validity_type {VALID, INVALID, QUIT};

// Function check if the coordinators enterd are valid
Validity_type is_valid
    (Game_board_type& game_board,
     unsigned int& x1, unsigned int& y1,
     unsigned int& x2, unsigned int& y2){

    // when x1 y1 x2 y2 are non-positive
    if(x1 == 0 or y1 == 0
       or
       x2 == 0 or y2 == 0){
        cout<<INVALID_CARD<<endl;
        return INVALID;
    }

    // when x1 y1 x2 y2 are not in range
    if(x1 > game_board.at(0).size()
       or y1 > game_board.size()
       or x2 > game_board.at(0).size()
       or y2 > game_board.size()){
        cout<<INVALID_CARD<<endl;
        return INVALID;
    }

    // when card is removed
    if(game_board.at(y1-1).at(x1-1).get_visibility() == EMPTY
      or game_board.at(y2-1).at(x2-1).get_visibility() == EMPTY){
        cout<<INVALID_CARD<<endl;
        return INVALID;
    }

   // when the same card is picked
    if(x1==x2 and y1 == y2){
        cout << INVALID_CARD <<endl;
        return INVALID;
    }

    return VALID;
}

// Find the greatest score
unsigned int find_max_score(Player_list_type players){
    unsigned int max_score = 0;
    for(auto player: players){
        if(player.number_of_pairs() > max_score){
            max_score = player.number_of_pairs();
        }
    }
    return max_score;
}

// Use the greatest score to find winner
Player_list_type find_winners
    (Player_list_type players, unsigned int max_score){
        Player_list_type list_of_winners;

    for(auto player : players){
        if(player.number_of_pairs()==max_score){
            list_of_winners.push_back(player);
        }
    }
    return list_of_winners;
}

int main()
{
    Game_board_type game_board;

    unsigned int factor1 = 1;
    unsigned int factor2 = 1;
    ask_product_and_calculate_factors(factor1, factor2);
    init_with_empties(game_board, factor1, factor2);

    string seed_str = "";
    std::cout << INPUT_SEED;
    std::getline(std::cin, seed_str);
    int seed = stoi_with_check(seed_str);
    init_with_cards(game_board, seed);

    // Lisää koodia
    // More code
    Player_list_type list_of_players;
    Ask_number_of_players(list_of_players);
    Player_list_type::size_type number_of_players = list_of_players.size();

    print(game_board);

    // Call the player turn-by-turn
    Player_list_type::size_type player_turn = 0;

    // Coordinators of 2 cards. reset everytime
    vector<unsigned int> coordinators;

    // Variable count: the maximum pairs
    for(unsigned int count = 1; count <= (factor1*factor2)/2;){
        // Define which player is in turn
        Player& player_in_turn = list_of_players.at(player_turn);

        Validity_type check_valid = INVALID;


        while(check_valid == INVALID){
            // Clear all element of coordinators in case
            // there is error in the previuos loop
            coordinators.clear();

            cout<<player_in_turn.get_name()
                <<": Enter two cards (x1, y1, x2, y2), or q to quit: ";

            for(int i=0; i<4; i++){

                string input;
                unsigned int input_converted = 0;
                cin >> input;

                //
                if(i==0){
                    if(input == "q"){
                        cout << GIVING_UP<<endl;
                        return EXIT_SUCCESS;
                    }else{
                        input_converted = stoi_with_check(input);
                        coordinators.push_back(input_converted);
                    }
                }else{
                    input_converted = stoi_with_check(input);
                    coordinators.push_back(input_converted);
                }
            }
            // Check the validity
            // if invalid, repeat the loop
            check_valid = is_valid(game_board,
                            coordinators.at(0),
                            coordinators.at(1),
                            coordinators.at(2),
                            coordinators.at(3));



        }

        // convert the coordinators to size_type
         Game_row_type::size_type x1 = coordinators.at(0) - 1;
         Game_board_type::size_type y1 = coordinators.at(1) - 1;
         Game_row_type::size_type x2 = coordinators.at(2) - 1;
         Game_board_type::size_type y2 = coordinators.at(3) - 1;

        //turn 2 cards each turn
        game_board.at(y1).at(x1).turn();
        game_board.at(y2).at(x2).turn();

        print(game_board);

        // check if a pair is found
        if(game_board.at(y1).at(x1).get_letter()
            ==game_board.at(y2).at(x2).get_letter()){
            player_in_turn.add_card(game_board.at(y1).at(x1));
            player_in_turn.add_card(game_board.at(y2).at(x2));
            cout<<FOUND<<endl;
            count = count + 1;
        }else{
            cout<<NOT_FOUND<<endl;
            game_board.at(y1).at(x1).turn();
            game_board.at(y2).at(x2).turn();

            // Change turn
            // Use modulo to start over again
            player_turn++;
            player_turn %= number_of_players;
        }





        // Print the score of all players
        for(Player_list_type::size_type i = 0;
            i < number_of_players;i++){
            list_of_players.at(i).print();
        }

        // Print all the card again but hidden
        print(game_board);
    }
    cout<<GAME_OVER<<endl;


    // The score of winner
    unsigned int winner_score;
    winner_score = find_max_score(list_of_players);

    // Make a winner list
    Player_list_type winner_list;
    winner_list = find_winners(list_of_players, winner_score);

    // Number of winner;
    vector<Player_list_type::size_type>::size_type number_of_winner;
    number_of_winner = winner_list.size();

    // If there is only 1 winner
    if(number_of_winner == 1){
        Player winner = list_of_players.at(0);
        cout<<winner.get_name()<<" has won with "
           << winner.number_of_pairs() << " pairs."<<endl;

     // In case there is multiple winner
    }else{
        cout<<"Tie of "<<number_of_winner<<" players with "
           << winner_score<< " pairs."<<endl;
    }
    return EXIT_SUCCESS;
}

