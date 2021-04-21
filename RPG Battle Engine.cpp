/* Battle mode for a text based RPG,
complete w/ save file!
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <fstream>

using namespace std;

int attack_damage (int attack_stat ,string vulnerable = "normal" );
string vulnerability (string offense_element, string defense_element, int offense_lv = 0, int defense_lv = 0);
string element ();

int main ()
{
    //Stats
    const int player_start_hp = 100,
              player_start_mp = 10,
              player_start_attack = 10;

    int player_hp_max = player_start_hp,
        player_mp_max = player_start_mp,
        player_hp = player_hp_max,
        player_mp = player_mp_max,
        player_attack = player_start_attack,

        player_gold = 0;


    int damage;

    string player_vulnerability = "normal",
           enemy_vulnerability = "normal";

    //Player Menu choices
    int player_action,
        player_spell,
        player_item,
        player_damage = 10;

    //Enemy Random choices/stats
    int enemy_action,
        enemy_attack = 70,
        enemy_magic_1_stat = 15,
        enemy_magic_2_stat = 15,
        enemy_hp = 100,
        enemy_damage = 10,
        enemy_gold = 50,

        enemy_magic_1 = enemy_attack + enemy_magic_1_stat,
        enemy_magic_2 = enemy_magic_1 + enemy_magic_2_stat,

        enemy_lv = 1;

    //Enemy Specific State
    int enemy_index = 1;

    string enemy_type = element(),
           enemy_name = enemy_type + " Hobgoblin Lv. " + to_string (enemy_lv),
           enemy_spell;

    string spell_1 = "Fart",
           spell_2 = "Smelly Belch",
           enemy_idle = "picked his nose";


    //Player Magic
    bool player_has_magic = true;
    int fire_lv = 0,
        fire_mp = 5,
        water_lv = 0,
        water_mp = 5,
        earth_lv = 0,
        earth_mp = 5,
        thunder_lv = 0,
        thunder_mp = 5;

    //Shop
    int price_increase = 10,
        fire_price = 30,
        water_price = 30,
        earth_price = 30,
        thunder_price = 30,
        potion_price = 5,
        super_potion_price = 100,
        ether_price = 50,
        bomb_price = 25,
        health_stat_price = 50,
        attack_stat_price = 20,
        magic_stat_price = 20;

    int player_hp_increase = 10,
        player_mp_increase = 10,
        player_attack_increase = 10;


    //Player Inventory
    bool player_has_item = true;
    int potion_number = 3,
        super_potion_number = 1,
        ether_number = 1,
        bomb_number = 2;


    //Game phase conditions
    bool game_running = true,
         battle,
         shop = false,
         player_menu,
         item_menu = false,
         magic_menu = false,
         shop_menu = false,
         magic_upgrade_menu = false,
         buy_item_menu = false,
         stat_upgrade_menu = false,
         continue_to_battle_menu = false;

    srand (time(NULL));

    ifstream fin;
    ofstream fout;

    bool start_menu = true;
    bool new_game_select_menu = false;
    bool continue_select_menu = false;

    bool has_data = false;

    char player_file_select;

//Main Menu
    while (start_menu)
    {
        cout << "Welcome to the RPG Turn-Based Battle Engine!" << endl
             << "What would you like to do?" << endl << endl
             << "1) New Game" << endl
             << "2) Continue" << endl
             << "3) Exit" << endl << endl;

        cin >> player_action;
        cout << endl;

        switch (player_action)
        {
        case 1: cout << "You chose New Game " << endl << endl;
                new_game_select_menu = true;

                break;
        case 2: cout << "You chose Continue " << endl << endl;
                continue_select_menu = true;

                break;
        case 3: cout << "You chose Exit " << endl << endl;

                return 0;
                break;
        default: cout << "***ERROR - Invalid Input***" << endl << endl;
        }

        while (new_game_select_menu)
        {
            cout << "Choose a file." << endl
                 << "WARNING: This will erase that file's current sava data!" << endl << endl
                 << "1) FILE A" << endl
                 << "2) FILE B" << endl
                 << "3) FILE C" << endl
                 << "4) ***Go Back***" << endl << endl;

            cin >> player_action;
            cout << endl;

            switch (player_action)
            {
            case 1: cout << "You chose FILE A " << endl << endl;
                    player_file_select = 'A';

                    new_game_select_menu = false;
                    start_menu = false;

                    break;
            case 2: cout << "You chose FILE B " << endl << endl;
                    player_file_select = 'B';

                    new_game_select_menu = false;
                    start_menu = false;

                    break;
            case 3: cout << "You chose FILE C " << endl << endl;
                    player_file_select = 'C';

                    new_game_select_menu = false;
                    start_menu = false;

                    break;
            case 4: cout << "You chose to Go Back." << endl << endl;

                    break;
            default: cout << "***ERROR - Invalid Input***" << endl << endl;
            }
        }

                while (continue_select_menu)
        {
            cout << "Choose a file to resume your game." << endl << endl
                 << "1) FILE A" << endl
                 << "2) FILE B" << endl
                 << "3) FILE C" << endl
                 << "4) ***Go Back***" << endl << endl;

            cin >> player_action;
            cout << endl;

            switch (player_action)
            {
            case 1: cout << "You chose FILE A " << endl << endl;
                    player_file_select = 'A';

                    continue_select_menu = false;
                    start_menu = false;

                    break;
            case 2: cout << "You chose FILE B " << endl << endl;
                    player_file_select = 'B';

                    continue_select_menu = false;
                    start_menu = false;

                    break;
            case 3: cout << "You chose FILE C " << endl << endl;
                    player_file_select = 'C';

                    continue_select_menu = false;
                    start_menu = false;

                    break;
            case 4: cout << "You chose to Go Back." << endl << endl;

                    break;
            default: cout << "***ERROR - Invalid Input***" << endl << endl;
            }

            if (player_file_select == 'A')
            {
                fin.open ("RPG_Battle_Engine_FILE_A");
                if (!fin)
                {
                    cout << " ***ERROR - FILE A doesn't exist***" << endl
                         << "Please choose again." << endl << endl;

                         continue_select_menu = true;
                         start_menu = true;
                }
            }
            else if (player_file_select == 'B')
            {
                fin.open ("RPG_Battle_Engine_FILE_B");
                if (!fin)
                {
                    cout << " ***ERROR - FILE B doesn't exist***" << endl
                         << "Please choose again." << endl << endl;

                         continue_select_menu = true;
                         start_menu = true;
                }
            }
            else if (player_file_select == 'C')
            {
                fin.open ("RPG_Battle_Engine_FILE_C");
                if (!fin)
                {
                    cout << " ***ERROR - FILE C doesn't exist***" << endl
                         << "Please choose again." << endl << endl;

                         continue_select_menu = true;
                         start_menu = true;
                }
            }
        }

    }

// Initialize files (read from in file, set up out file to save after shop phase
    if (fin)
    {
        fin >> has_data;
        if (has_data)
        {
            cout << "Loading File..." << endl << endl;

        fin  >> player_hp_max
             >> player_mp_max
             >> player_hp
             >> player_mp
             >> player_attack
             >> player_gold;

        fin  >> enemy_attack
             >> enemy_magic_1_stat
             >> enemy_magic_2_stat
             >> enemy_hp
             >> enemy_damage
             >> enemy_gold
             >> enemy_magic_1
             >> enemy_magic_2
             >> enemy_lv
             >> enemy_index;

             getline(fin, enemy_type);
             getline(fin, enemy_type);
             getline(fin, enemy_name);

             if (enemy_name == "")
                getline(fin, enemy_name);

             getline(fin, spell_1);
             getline(fin, spell_2);
             getline(fin, enemy_idle);

        fin  >> player_has_magic
             >> fire_lv
             >> fire_mp
             >> water_lv
             >> water_mp
             >> earth_lv
             >> earth_mp
             >> thunder_lv
             >> thunder_mp;

        fin  >> fire_price
             >> water_price
             >> earth_price
             >> thunder_price
             >> potion_price
             >> super_potion_price
             >> ether_price
             >> bomb_price
             >> health_stat_price
             >> attack_stat_price
             >> magic_stat_price;

        fin  >> player_has_item
             >> potion_number
             >> super_potion_number
             >> ether_number
             >> bomb_number;
            system("PAUSE>NUL");
        }
    }

    fin.close();

    while (game_running)
    {
       if (enemy_name == "Chuck Norris" || enemy_name == "chuck norris" || enemy_name == "Chuck norris" || enemy_name == "chuck Norris")
       {
           cout << "WOW!" << endl
                << "You decided to wish for death!" << endl;

                system("PAUSE>NUL");

           cout << "You challenged Chuck Norris!" << endl << endl;

                cout << "Player HP: " << setw(3) << player_hp
                << "                               Enemy HP: 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999 "
                << endl
                << "       MP: " << setw(3) << player_mp
                << endl << endl;

            cout << "Choose your action: " << endl << endl
                    << "1) Attack " << endl
                    << "2) Magic " << endl
                    << "3) Item " << endl << endl;

            cin >> player_action;
            cout << endl;

            cout << "You tried to take your turn!" << endl;

            system("PAUSE>NUL");

            cout << "But Chuck Norris said 'Yoink'!" << endl
                 << "Chuck Norris takes your turn for you!" << endl << endl;

            system("PAUSE>NUL");

            cout << "Chuck Norris used Yeet Innocent Bystander!" << endl
                 << "You got hit with what was left of an Innocent Bystander!" << endl;

            system("PAUSE>NUL");

            cout << "You take 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999 damage!" << endl << endl;

            system("PAUSE>NUL");

            cout << "Needless to say, you are more than dead!" << endl;

            system("PAUSE>NUL");

            cout   << "Chuck Norris laughs at your smoking crater!" << endl << endl;

            return 42;

       }
       cout << "A " << enemy_name << " approaches!" << endl << endl;
       system ("PAUSE>NUL");
       battle = true;

       while (battle)
       {
           if (player_mp < 0)
               player_mp = 0;

           cout << "Player HP: " << setw(3) << player_hp
                << "                               Enemy HP: "
                << setw(3) << enemy_hp << endl
                << "       MP: " << setw(3) << player_mp
                << endl << endl;

           player_menu = true;

           while (player_menu)
           {
               //Player choose action
               cout << "Choose your action: " << endl << endl
                    << "1) Attack " << endl
                    << "2) Magic " << endl
                    << "3) Item " << endl << endl;

               cin >> player_action;
               cout << endl;

               switch (player_action)
               {
                   case 1: cout << "You chose Attack." << endl << endl;

                           //Execute Attack
                           damage = attack_damage(player_attack);
                           enemy_hp -= damage;
                           cout << enemy_name << " took " << damage << " damage!" << endl << endl;

                           player_menu = false;
                           system("PAUSE>NUL");
                           break;

                   case 2: cout << "You chose Magic." << endl << endl;

                           if (player_has_magic == false)
                           {
                               cout << "You don't know any spells!"
                                    << endl << endl;
                           }
                           else
                           {
                               magic_menu = true;

                               while (magic_menu)
                               {
                                   if (player_mp < 0)
                                       player_mp = 0;

                                   cout << "Choose your spell: " << endl
                                        << "       MP: " << setw(3) << player_mp << endl << endl;

                                   if (fire_lv > 0)
                                      cout << "1) Fire      Lv. " << fire_lv
                                           << "      MP: " << setw(2) << fire_mp << endl;
                                   else
                                      cout << "1) -------------------" << endl;

                                   if (water_lv > 0)
                                      cout << "2) Water     Lv. " << water_lv
                                      << "      MP: " << setw(2) << water_mp << endl;
                                   else
                                      cout << "2) -------------------" << endl;

                                   if (earth_lv > 0)
                                      cout << "3) Earth     Lv. " << earth_lv
                                      << "      MP: " << setw(2) << earth_mp << endl;
                                   else
                                      cout << "3) -------------------" << endl;

                                   if (thunder_lv > 0)
                                      cout << "4) Thunder   Lv. " << thunder_lv
                                      << "      MP: " << setw(2) << thunder_mp << endl;
                                   else
                                      cout << "4) -------------------" << endl;

                                   cout << "5) ***Go Back*** " << endl << endl;

                                   cin >> player_action;
                                   cout << endl;

                                   switch (player_action)
                                   {
                                   case 1: if (fire_lv > 0)
                                               if (player_mp >= fire_mp)
                                               {
                                                   cout << "You chose Fire Lv. " << fire_lv << "." << endl << endl;

                                                   player_mp -= fire_mp;
                                                   magic_menu = false;
                                                   player_menu = false;

                                                   // Execute fire damage
                                                   damage = attack_damage(player_attack, vulnerability("Fire", enemy_type));
                                                   damage *= (fire_lv/4) + 1;
                                                   enemy_hp -= damage;

                                                   if (vulnerability("Fire", enemy_type) == "weak")
                                                       cout << enemy_name << " is strong against fire!" << endl;
                                                   else if (vulnerability("Fire", enemy_type) == "strong")
                                                       cout << enemy_name << " is weak against fire!" << endl;

                                                       cout << enemy_name << " took " << damage << " damage!" << endl << endl;

                                                   system("PAUSE>NUL");
                                               }
                                               else
                                                   cout << "Not enough MP!" << endl << endl;
                                           else
                                               cout << "***ERROR - Invalid Input!***" << endl << endl;

                                           break;

                                   case 2: if (water_lv > 0)
                                               if (player_mp >= water_mp)
                                               {
                                                   cout << "You chose Water Lv. " << water_lv << "." << endl << endl;

                                                   player_mp -= water_mp;
                                                   magic_menu = false;
                                                   player_menu = false;

                                                   //Execute water damage
                                                   damage = attack_damage(player_attack, vulnerability("Water", enemy_type));
                                                   damage *= (water_lv/4) + 1;
                                                   enemy_hp -= damage;

                                                   if (vulnerability("Water", enemy_type) == "weak")
                                                       cout << enemy_name << " is strong against water!" << endl;
                                                   else if (vulnerability("Water", enemy_type) == "strong")
                                                       cout << enemy_name << " is weak against water!" << endl;

                                                       cout << enemy_name << " took " << damage << " damage!" << endl << endl;

                                                   system("PAUSE>NUL");
                                               }
                                               else
                                                   cout << "Not enough MP!" << endl << endl;
                                           else
                                               cout << "***ERROR - Invalid Input!***" << endl << endl;

                                           break;
                                   case 3: if (earth_lv > 0)
                                               if (player_mp >= earth_mp)
                                               {
                                                   cout << "You chose Earth Lv. " << earth_lv << "." << endl << endl;

                                                   player_mp -= earth_mp;
                                                   magic_menu = false;
                                                   player_menu = false;

                                                   // Execute earth damage

                                                   damage = attack_damage(player_attack, vulnerability("Earth", enemy_type));
                                                   damage *= (earth_lv/4) + 1;
                                                   enemy_hp -= damage;

                                                   if (vulnerability("Earth", enemy_type) == "weak")
                                                       cout << enemy_name << " is strong against earth!" << endl;
                                                   else if (vulnerability("Earth", enemy_type) == "strong")
                                                       cout << enemy_name << " is weak against earth!" << endl;

                                                       cout << enemy_name << " took " << damage << " damage!" << endl << endl;

                                                   system("PAUSE>NUL");
                                               }
                                               else
                                                   cout << "Not enough MP!" << endl << endl;
                                           else
                                               cout << "***ERROR - Invalid Input!***" << endl << endl;

                                           break;
                                   case 4: if (thunder_lv > 0)
                                               if (player_mp >= thunder_mp)
                                               {
                                                   cout << "You chose Thunder Lv. " << thunder_lv << "." << endl << endl;

                                                   player_mp -= thunder_mp;
                                                   magic_menu = false;
                                                   player_menu = false;

                                                   // Execute thunder damage
                                                   damage = attack_damage(player_attack, vulnerability("Thunder", enemy_type));
                                                   damage *= (thunder_lv/4) + 1;
                                                   enemy_hp -= damage;

                                                   if (vulnerability("Thunder", enemy_type) == "weak")
                                                       cout << enemy_name << " is strong against thunder!" << endl;
                                                   else if (vulnerability("Thunder", enemy_type) == "strong")
                                                       cout << enemy_name << " is weak against thunder!" << endl;

                                                       cout << enemy_name << " took " << damage << " damage!" << endl << endl;

                                                   system("PAUSE>NUL");
                                               }
                                               else
                                                   cout << "Not enough MP!" << endl << endl;
                                           else
                                               cout << "***ERROR - Invalid Input!***" << endl << endl;

                                           break;
                                   case 5: cout << "You chose to Go Back." << endl << endl;
                                           magic_menu = false;

                                           break;
                                   default: cout << "***ERROR - Invalid Input***" << endl << endl;
                                   }

                               }
                           }

                           break;
                   case 3: cout << "You chose Item." << endl << endl;

                           if (player_has_item == false)
                           {
                               cout << "You don't have any items!"
                                    << endl << endl;
                           }
                           else
                           {
                               item_menu = true;

                               while (item_menu)
                               {
                                   cout << "Choose your your item: " << setw(2) << endl << endl;

                                   if (potion_number > 0)
                                      cout << "1) Potion          x" << setw(2) << potion_number << endl;
                                   else
                                      cout << "1) -------------------" << endl;

                                   if (super_potion_number > 0)
                                      cout << "2) Super Potion    x" << setw(2) << super_potion_number << endl;
                                   else
                                      cout << "2) -------------------" << endl;

                                   if (ether_number > 0)
                                      cout << "3) Ether           x" << setw(2) << ether_number << endl;
                                   else
                                      cout << "3) -------------------" << endl;

                                   if (bomb_number > 0)
                                      cout << "4) Bomb            x" << setw(2) << bomb_number << endl;
                                   else
                                      cout << "4) -------------------" << endl;

                                   cout << "5) ***Go Back*** " << endl << endl;

                                   cin >> player_action;
                                   cout << endl;

                                   switch (player_action)
                                   {
                                   case 1: if (potion_number > 0)
                                           {
                                                   cout << "You chose to use a Potion. " << endl << endl;

                                                   potion_number--;
                                                   item_menu = false;
                                                   player_menu = false;

                                                   // Execute potion effect

                                                   player_hp += 50;
                                                   if (player_hp > player_hp_max)
                                                       player_hp = player_hp_max;

                                                    if (potion_number <= 0 && super_potion_number <= 0 && ether_number <= 0 && bomb_number <=0)
                                                        player_has_item = false;

                                                   cout << "You healed 50 HP!" << endl << endl;

                                                   system("PAUSE>NUL");
                                           }
                                           else
                                               cout << "***ERROR - Invalid Input!***" << endl << endl;

                                           break;
                                   case 2: if (super_potion_number > 0)
                                               {
                                                   cout << "You chose to use a Super Potion. " << endl << endl;

                                                   super_potion_number --;
                                                   item_menu = false;
                                                   player_menu = false;

                                                   // Execute super potion effect

                                                   player_hp += 200;
                                                   if (player_hp > player_hp_max)
                                                       player_hp = player_hp_max;

                                                    if (potion_number <= 0 && super_potion_number <= 0 && ether_number <= 0 && bomb_number <=0)
                                                        player_has_item = false;

                                                   cout << "You healed 200 HP!" << endl << endl;

                                                   system("PAUSE>NUL");
                                               }
                                           else
                                               cout << "***ERROR - Invalid Input!***" << endl << endl;

                                           break;
                                   case 3: if (ether_number > 0)
                                               {
                                                   cout << "You chose to use an Ether. " << endl << endl;

                                                   ether_number--;
                                                   item_menu = false;
                                                   player_menu = false;

                                                   // Execute ether effect

                                                   player_mp += 30;
                                                   if (player_mp > player_mp_max)
                                                       player_mp = player_mp_max;

                                                    if (potion_number <= 0 && super_potion_number <= 0 && ether_number <= 0 && bomb_number <=0)
                                                        player_has_item = false;

                                                   cout << "You regained 30 MP!" << endl << endl;

                                                   system("PAUSE>NUL");
                                               }
                                           else
                                               cout << "***ERROR - Invalid Input!***" << endl << endl;

                                           break;
                                   case 4: if (bomb_number > 0)
                                               if (player_mp >= thunder_mp)
                                               {
                                                   cout << "You chose to use a Bomb. " << endl << endl;

                                                   bomb_number--;
                                                   item_menu = false;
                                                   player_menu = false;

                                                   // Execute bomb damage

                                                   enemy_hp -= 200;

                                                   if (potion_number <= 0 && super_potion_number <= 0 && ether_number <= 0 && bomb_number <=0)
                                                        player_has_item = false;

                                                   cout << enemy_name << " took 200 " << " damage!" << endl << endl;

                                                   system("PAUSE>NUL");
                                               }
                                           else
                                               cout << "***ERROR - Invalid Input!***" << endl << endl;

                                           break;
                                   case 5: cout << "You chose to Go Back." << endl << endl;
                                           item_menu = false;

                                           break;
                                   default: cout << "***ERROR - Invalid Input***" << endl << endl;
                                   }

                               }
                           }

                           break;
                   default: cout << "***ERROR - Invalid Input!***" << endl << endl;
               }
           }
           if (enemy_hp <= 0)
           {
               cout << "You defeated " << enemy_name << "!" << endl << endl;
               system ("PAUSE>NUL");

               cout << "The Mysterious Shopkeeper approaches!" << endl << endl;
               system ("PAUSE>NUL");
               battle = false;
           }

// Enemy Turn
           if (battle)
           {
               enemy_action = rand() % 101;

               if (enemy_action <= enemy_attack)
               {
                   cout << enemy_name << " attacked!" << endl << endl;
                   //Execute Attack
                   damage = attack_damage(enemy_damage);
                   player_hp -= damage;
                   cout << "You took " << damage << " damage!" << endl << endl;
               }
               else if (enemy_action <= enemy_magic_1)
               {
                   cout << enemy_name << " used " << spell_1 << "!" << endl;

                   //Execute Spell 1
                   enemy_spell = spell_1;
               }
               else if (enemy_action <= enemy_magic_2)
               {
                   cout << enemy_name << " used " << spell_2 << "!" << endl;

                   //Execute Spell 2
                   enemy_spell = spell_2;
               }
               else
               {
                   cout << enemy_name << " " << enemy_idle << "!" << endl << endl;
               }

               //Resolve Magic spells (if used)
                   if (enemy_spell == "Fart") //deal weak fire damage
                    {
                        // Execute fire damage
                        damage = attack_damage(enemy_damage, vulnerability("Fire", "Earth", enemy_lv ,fire_lv + 2));
                        damage *= (enemy_lv/4) + 1;
                        player_hp -= damage;

                        if (vulnerability("Fire", "Earth", enemy_lv ,fire_lv + 2) == "strong")
                            cout << "But you are weak against fire!" << endl;
                        else
                            cout << "But you are strong against fire!" << endl;

                            cout << "You took " << damage << " damage!" << endl << endl;
                    }
                    else if (enemy_spell == "Smelly Belch") //destroys a random item
                    {
                        enemy_action = rand() % 3;

                        switch (enemy_action)
                        {
                        case 0:if (potion_number > 0)
                                    {
                                        potion_number--;
                                        cout << "The stench disintegrated a potion!" << endl << endl;
                                    }
                                    else cout << "But nothing happended!" << endl << endl;
                                    break;
                        case 1:if (super_potion_number > 0)
                                    {
                                        super_potion_number--;
                                        cout << "The stench disintegrated a super potion!" << endl << endl;
                                    }
                                    else cout << "But nothing happended!" << endl << endl;
                                    break;
                        case 2:if (ether_number > 0)
                                    {
                                        ether_number--;
                                        cout << "The stench disintegrated an ether!" << endl << endl;
                                    }
                                    else cout << "But nothing happended!" << endl << endl;
                                    break;
                        case 3:if (bomb_number > 0)
                                    {
                                        bomb_number--;
                                        cout << "The stench disintegrated a bomb!" << endl << endl;
                                    }
                                    else cout << "But nothing happended!" << endl << endl;
                                    break;
                        }

                    }
                    else if (enemy_spell == "Pick Pocket") // Lose gold permanently
                    {
                        if (player_gold > 0)
                        {
                            int stolen_gold = rand() % (enemy_lv * 8) + enemy_lv;
                            player_gold -= stolen_gold;

                            if (player_gold < 0)
                                player_gold = 0;

                            cout << enemy_name << " stole " << stolen_gold << " gold!" << endl << endl;
                        }
                        else
                            cout << "But you have no gold!" << endl << endl;

                    }
                    else if (enemy_spell == "Draining Bite") // Lose MP temporarily
                    {
                        if (player_mp > 0)
                        {
                            int stolen_mp = rand() % (enemy_lv * 8) + enemy_lv;
                            player_mp -= stolen_mp;

                            if (player_mp < 0)
                                player_mp = 0;

                            cout << enemy_name << " stole " << stolen_mp << " MP!" << endl << endl;
                        }
                        else
                            cout << "But you have no MP!!" << endl << endl;

                    }
                    else if (enemy_spell == "Claw") // deal two attacks
                    {
                        damage = attack_damage(enemy_damage);
                        player_hp -= damage;
                        cout << "You took " << damage << " damage!" << endl << endl;

                        system("PAUSE>NUL");

                        cout << enemy_name << " used " << spell_1 << " again!" << endl << endl;
                        damage = attack_damage(enemy_damage);
                        player_hp -= damage;
                        cout << "You took " << damage << " damage!" << endl << endl;
                    }
                    else if (enemy_spell == "Breath Weapon") // deal Magic damage according to enemy's type
                    {
                        // Execute magic damage (buggy!)
                        if (enemy_type == "Fire")
                        {
                            damage = attack_damage(enemy_damage, vulnerability(enemy_type, "Earth" , enemy_lv ,fire_lv + 2));

                            if (vulnerability("Fire", "Earth") == "weak")
                                cout << "But you are strong against fire!" << endl;
                            else if (vulnerability("Fire", "Earth") == "strong")
                                cout << " But you are weak against fire!" << endl;
                        }
                        else if (enemy_type == "Earth")
                        {
                            damage = attack_damage(enemy_damage, vulnerability(enemy_type, "Thunder" , enemy_lv ,fire_lv + 2));

                            if (vulnerability("Earth", "Thunder") == "weak")
                                cout << "But you are strong against earth!" << endl;
                            else if (vulnerability("Earth", "Thunder") == "strong")
                                cout << " But you are weak against earth!" << endl;
                        }
                        else if (enemy_type == "Thunder")
                        {
                            damage = attack_damage(enemy_damage, vulnerability(enemy_type, "Water" , enemy_lv ,fire_lv + 2));

                            if (vulnerability("Thunder", "Water") == "weak")
                                cout << "But you are strong against thunder!" << endl;
                            else if (vulnerability("Thunder", "Water") == "strong")
                                cout << " But you are weak against thunder!" << endl;
                        }
                        else if (enemy_type == "Water")
                        {
                            damage = attack_damage(enemy_damage, vulnerability(enemy_type, "Fire" , enemy_lv ,fire_lv + 2));

                            if (vulnerability("Water", "Fire") == "weak")
                                cout << "But you are strong against water!" << endl;
                            else if (vulnerability("Water", "Fire") == "strong")
                                cout << " But you are weak against water!" << endl;
                        }
                        else
                        {
                            damage = 0;
                            cout << "But " << enemy_name << "can't use magic!" << endl;
                        }

                        damage *= (enemy_lv/4) + 1;
                        player_hp -= damage;

                            cout << "You took " << damage << " damage!" << endl << endl;
                    }

               system("PAUSE>NUL");

               if (player_hp <= 0)
               {
                   enemy_action = rand() % 3;
                   switch (enemy_action)
                   {
                       case 0: cout << "You were massacred by " << enemy_name << "!" << endl << endl;
                               break;
                       case 1: cout << "You were mauled by " << enemy_name << "!" << endl << endl;
                               break;
                       case 2: cout << "You were gutted and left for dead by " << enemy_name << "!" << endl << endl;
                               break;
                       case 3: cout << "You were absolutely destroyed by " << enemy_name << "!" << endl << endl;
                               break;
                   }

                   battle = false;
                   game_running = false;
                   system ("PAUSE>NUL");
               }
           }

       }

//Prepare Next Battle
       enemy_index++;
       switch (enemy_index)
       {
       case 1: //Hobgoblin
               enemy_lv++;

               enemy_hp = 50 + enemy_lv * 50;
               enemy_damage = enemy_lv * 5;

               enemy_attack = 70;
               enemy_magic_1_stat = 15;
               enemy_magic_2_stat = 15;

               enemy_magic_1 = enemy_attack + enemy_magic_1_stat;
               enemy_magic_2 = enemy_magic_1 + enemy_magic_2_stat;

               enemy_type = element();
               enemy_name = enemy_type + " Hobgoblin Lv. " + to_string (enemy_lv);

               spell_1 = "Fart"; //deal weak fire damage
               spell_2 = "Smelly Belch"; //destroys a random item
               enemy_idle = "picked his nose";

               break;

       case 2: //Rodent of Incredible Size
               enemy_hp = 50 + enemy_lv * 50;
               enemy_damage =  enemy_lv * 7;

               enemy_attack = 50;
               enemy_magic_1_stat = 10;
               enemy_magic_2_stat = 40;

               enemy_magic_1 = enemy_attack + enemy_magic_1_stat;
               enemy_magic_2 = enemy_magic_1 + enemy_magic_2_stat;

               enemy_type = element();
               enemy_name = enemy_type + " Rodent of Incredible Size Lv. " + to_string (enemy_lv);

               spell_1 = "Pick Pocket"; // Lose gold permanently
               spell_2 = "Draining Bite"; // Lose MP temporarily
               enemy_idle = "beadily eyed you";

               break;

       case 3: //Jabberwocky (Boss)
               enemy_hp = 100 + enemy_lv;
               enemy_damage = 10 + enemy_lv;

               enemy_attack = 45;
               enemy_magic_1_stat = 10;
               enemy_magic_2_stat = 45;

               enemy_magic_1 = enemy_attack + enemy_magic_1_stat;
               enemy_magic_2 = enemy_magic_1 + enemy_magic_2_stat;

               enemy_type = element();
               enemy_name = enemy_type + " Jabberwocky Lv. " + to_string (enemy_lv);

               spell_1 = "Claw"; // deal two attacks
               spell_2 = "Breath Weapon"; // deal Magic damage according to enemy's type
               enemy_idle = "flashed a toothy grin";

               enemy_index = 0;

               break;
       }

//Shop
       if (player_hp > 0)
          shop_menu = true;

        player_gold += enemy_gold;
        enemy_gold = 50 * enemy_lv;
        enemy_gold += rand() % enemy_gold - 7;

       while (shop_menu)
       {   cout << "     *** 'in a rugged Australian accent' ***" << endl
                << "Welcome stranger! I've got a good selection of goods on sale!" << endl
                << "Gold: " << setw(4) << player_gold << endl << endl
                << "1) Spells " << endl
                << "2) Items " << endl
                << "3) Stat Upgrades " << endl
                << "4) ***Leave*** " << endl << endl;

           cin >> player_action;
           cout << endl << endl;

           switch (player_action)
           {
                case  1: cout << "You chose Spells." << endl << endl;
                        magic_upgrade_menu = true;

                        break;
                case 2: cout << "You chose Items." << endl << endl;
                        buy_item_menu = true;

                        break;
                case 3: cout << "You chose Stat Upgrades." << endl << endl;
                        stat_upgrade_menu = true;

                        break;
                case 4: cout << "You chose to Leave." << endl << endl;
                        shop_menu = false;

                        break;
                default: cout << "***ERROR - Invalid Input!***" << endl << endl;
           }

           while (magic_upgrade_menu)
           {
               cout << "What are ya buyin'?" << endl << endl
                    << "1) Fire    Lv." << fire_lv +1 << "      " << setw(3) << fire_price << " Gold" << endl
                    << "2) Water   Lv." << water_lv +1 << "      " << setw(3) << water_price << " Gold" << endl
                    << "3) Earth   Lv." << earth_lv +1 << "      " << setw(3) << earth_price << " Gold" << endl
                    << "4) Thunder Lv." << thunder_lv +1 << "      " << setw(3) << thunder_price << " Gold" << endl
                    << "5) ***Go Back*** " << endl << endl;

               cin >> player_action;
               cout << endl << endl;

               switch (player_action)
               {
               case 1: if (player_gold >= fire_price)
                       {
                       cout << "You chose Fire Lv." << fire_lv + 1 << "." << endl
                            << "Your spell has been upgraded!" << endl<< endl;

                        player_has_magic = true;

                       fire_lv += 1;
                       player_gold -= fire_price;
                       fire_price += fire_lv * price_increase;
                       fire_mp = fire_lv * 4;
                       magic_upgrade_menu = false;
                       }
                       else
                           cout << "Not enough cash!" << endl << endl;

                   break;
               case 2: if (player_gold >= water_price)
                       {
                       cout << "You chose Water Lv." << water_lv + 1 << "." << endl
                            << "Your spell has been upgraded!" << endl << endl;

                        player_has_magic = true;

                       water_lv += 1;
                       player_gold -= water_price;
                       water_price += water_lv * price_increase ;
                       water_mp = water_lv * 4;
                       magic_upgrade_menu = false;
                       }
                       else
                           cout << "Not enough cash!" << endl << endl;

                   break;
               case 3: if (player_gold >= earth_price)
                       {
                       cout << "You chose Earth Lv." << earth_lv + 1 << "." << endl
                            << "Your spell has been upgraded!" << endl <<endl;

                        player_has_magic = true;

                       earth_lv += 1;
                       player_gold -= earth_price;
                       earth_price += earth_lv * price_increase;
                       earth_mp = earth_lv * 4;
                       magic_upgrade_menu = false;
                       }
                       else
                           cout << "Not enough cash!" << endl << endl;
                   break;
               case 4: if (player_gold >= thunder_price)
                       {
                       cout << "You chose Thunder Lv." << thunder_lv + 1 << "." << endl
                            << "Your spell has been upgraded!" << endl << endl;

                        player_has_magic = true;

                       thunder_lv += 1;
                       player_gold -= thunder_price;
                       thunder_price += thunder_lv * price_increase;
                       thunder_mp = thunder_lv * 4;
                       magic_upgrade_menu = false;
                       }
                       else
                           cout << "Not enough cash!" << endl << endl;

                   break;
               case 5: cout << "You chose to Go Back." << endl << endl;

                       magic_upgrade_menu = false;

                   break;
               default: cout << "***ERROR - Invalid Input!***" << endl << endl;
               }
           }

           while (buy_item_menu)
           {
               cout << "What are ya buyin'?" << endl << endl
                    << "1) Potion       " << "     " << setw(3) << potion_price << " Gold" << endl
                    << "2) Super Potion " << "     " << setw(3) << super_potion_price << " Gold" << endl
                    << "3) Ether        " << "     " << setw(3) << ether_price << " Gold" << endl
                    << "4) Bomb         " << "     " << setw(3) << bomb_price << " Gold" << endl
                    << "5) ***Go Back*** " << endl << endl;

               cin >> player_action;
               cout << endl << endl;

               switch (player_action)
               {
               case 1: if (player_gold >= potion_price)
                       {
                           cout << "You chose Potion." << endl
                                << "You put the potion into your bag." << endl << endl;

                           potion_number += 1;
                           player_gold -= potion_price;
                           buy_item_menu = false;
                       }
                       else
                           cout << "Not enough cash!" << endl << endl;
                   break;
               case 2: if (player_gold >= super_potion_price)
                       {
                           cout << "You chose Super Potion." << endl
                                << "You put the super potion into your bag." << endl << endl;

                           super_potion_number += 1;
                           player_gold -= super_potion_price;
                           buy_item_menu = false;
                       }
                       else
                           cout << "Not enough cash!" << endl << endl;
                   break;
               case 3: if (player_gold >= ether_price)
                       {
                           cout << "You chose Ether." << endl
                                << "You put the ether into your bag." << endl << endl;

                           ether_number += 1;
                           player_gold -= bomb_price;
                           buy_item_menu = false;
                       }
                       else
                           cout << "Not enough cash!" << endl << endl;
                   break;
               case 4: if (player_gold >= bomb_price)
                       {
                           cout << "You chose Bomb." << endl
                                << "You put the bomb into your bag." << endl << endl;

                           potion_number += 1;
                           player_gold -= bomb_price;
                           buy_item_menu = false;
                       }
                       else
                           cout << "Not enough cash!" << endl << endl;
                   break;
               case 5: cout << "You chose to Go Back." << endl << endl;

                       buy_item_menu = false;

                   break;
               default: cout << "***ERROR - Invalid Input!***" << endl << endl;
               }
           }

           while (stat_upgrade_menu)
           {
               cout << "What are ya buyin'?" << endl << endl
                    << "1) Health       " << "     " << setw(3) << health_stat_price << " Gold" << endl
                    << "2) Magic        " << "     " << setw(3) << magic_stat_price << " Gold" << endl
                    << "3) Attack       " << "     " << setw(3) << attack_stat_price << " Gold" << endl
                    << "4) ***Go Back*** " << endl << endl;

               cin >> player_action;
               cout << endl << endl;

               switch (player_action)
               {
               case 1: if (player_gold >= health_stat_price)
                       {
                           cout << "You chose Health." << endl
                                << "Your health has been upgraded!" << endl<< endl;

                           player_hp_max += player_hp_increase;
                           player_gold -= health_stat_price;
                           health_stat_price += ((player_hp_max - player_start_hp) / player_hp_increase) * price_increase;
                           stat_upgrade_menu = false;
                       }
                       else
                           cout << "Not enough cash!" << endl << endl;
                   break;
               case 2: if (player_gold >= magic_stat_price)
                       {
                           cout << "You chose Magic." << endl
                                << "Your magic has been upgraded!" << endl<< endl;

                           player_mp_max += player_mp_increase;
                           player_gold -= magic_stat_price;
                           magic_stat_price += ((player_mp_max - player_start_mp) / player_mp_increase) * price_increase;
                           stat_upgrade_menu = false;
                       }
                       else
                           cout << "Not enough cash!" << endl << endl;
                   break;
               case 3: if (player_gold >= attack_stat_price)
                       {
                           cout << "You chose Attack." << endl
                                << "Your attack has been upgraded!" << endl<< endl;

                           player_attack += player_attack_increase;
                           player_gold -= attack_stat_price;
                           attack_stat_price += ((player_attack - player_start_attack) / player_attack_increase) * price_increase;
                           stat_upgrade_menu = false;
                       }
                       else
                           cout << "Not enough cash!" << endl << endl;
                   break;
               case 4: cout << "You chose to Go Back." << endl << endl;

                       stat_upgrade_menu = false;
                   break;
               default: cout << "***ERROR - Invalid Input!***" << endl << endl;
               }
           }
       }

       if (player_hp > 0)
       {
       player_hp = player_hp_max;
       player_mp = player_mp_max;

       cout << "Saving Game..." << endl << endl;

//Save Game
        if (player_file_select == 'A')
        {
            fout.open ("RPG_Battle_Engine_FILE_A");
            if (!fout)
            {
                cout << " ***ERROR - Could not open file***" << endl
                        << "Shutting down..." << endl << endl;

                return 1;
            }
        }
        else if (player_file_select == 'B')
        {
            fout.open ("RPG_Battle_Engine_FILE_B");
            if (!fout)
            {
                cout << " ***ERROR - Could not open file***" << endl
                        << "Shutting down..." << endl << endl;

                return 1;
            }
        }
        else if (player_file_select == 'C')
        {
            fout.open ("RPG_Battle_Engine_FILE_C");
            if (!fout)
            {
                cout << " ***ERROR - Could not open file***" << endl
                        << "Shutting down..." << endl << endl;

                return 1;
            }
        }

        has_data = true;

        fout << has_data << endl;

        fout << player_hp_max << endl
             << player_mp_max << endl
             << player_hp << endl
             << player_mp << endl
             << player_attack << endl
             << player_gold << endl;

        fout << enemy_attack << endl
             << enemy_magic_1_stat << endl
             << enemy_magic_2_stat << endl
             << enemy_hp << endl
             << enemy_damage << endl
             << enemy_gold << endl
             << enemy_magic_1 << endl
             << enemy_magic_2 << endl
             << enemy_lv << endl
             << enemy_index << endl
             << enemy_type << endl
             << enemy_name << endl
             << spell_1 << endl
             << spell_2 << endl
             << enemy_idle << endl ;

        fout << player_has_magic << endl
             << fire_lv << endl
             << fire_mp << endl
             << water_lv << endl
             << water_mp << endl
             << earth_lv << endl
             << earth_mp << endl
             << thunder_lv << endl
             << thunder_mp << endl;

        fout << fire_price << endl
             << water_price << endl
             << earth_price << endl
             << thunder_price << endl
             << potion_price << endl
             << super_potion_price << endl
             << ether_price << endl
             << bomb_price << endl
             << health_stat_price << endl
             << attack_stat_price << endl
             << magic_stat_price << endl ;

        fout << player_has_item << endl
             << potion_number << endl
             << super_potion_number << endl
             << ether_number << endl
             << bomb_number << endl;

        fout << endl << endl << endl << endl << "Diggin' around in the save file, eh?" << endl
             << "Beware, messin' with the numbers here could make you like a god!" << endl
             << "That, or you could make your enemies turn into Chuck Norris on accident, heh, heh, heh!" << endl
             << endl;

        fout.close();

        system("PAUSE>NUL");
       }

    }
    cout << "..00000000..........0000........00..........00....000000000000............00000000......00........00....000000000000....00000000.." << endl
         << "00........00......00....00......0000......0000....00....................00........00....00........00....00..............00.......0" << endl
         << "00................00....00......0000.....00.00....00....................00........00....00........00....00..............00.......0" << endl
         << "00..............00........00....00.00....00.00....00....................00........00....00........00....00..............00.......0" << endl
         << "00..............00........00....00.00....00.00....00....................00........00....00........00....00..............00.....00." << endl
         << "00..............000000000000....00.00....00.00....000000000000..........00........00.....00......00.....000000000000....000000...." << endl
         << "00....000000....00........00....00..00..00..00....00....................00........00.....00......00.....00..............00...0...." << endl
         << "00........00....00........00....00..00..00..00....00....................00........00.....00......00.....00..............00....0..." << endl
         << "00........00....00........00....00..00..00..00....00....................00........00......00....00......00..............00.....0.." << endl
         << "00........00....00........00....00...0000...00....00....................00........00.......00..00.......00..............00......0." << endl
         << "..00000000......00........00....00....00....00....000000000000............00000000...........00.........000000000000....00.......0" << endl
         << endl << endl
         << "Thanks for playing!" << endl << endl;

}

int attack_damage (int attack_stat ,string vulnerable)
{
    int damage,
        damage_mod,
        attack_strike;

    srand (time(NULL));

    attack_strike = rand() % 101;

    if (attack_strike == 0)
        cout << "Attack misses!" << endl << endl;

    else if (attack_strike == 100)
    {
        cout << "Critical hit!" << endl << endl;
        attack_strike = 2;
    }
    else
    {
        attack_strike = 1;

        damage = 5 * attack_stat;
        damage_mod = damage/4;
        damage += rand() % damage_mod - damage_mod;

        damage *= attack_strike;

        if (vulnerable == "weak")
            damage /= 2;
        else if (vulnerable == "strong")
            damage *= 2;
        else
            damage = damage;


    }
    return damage;
}

string vulnerability (string offense_element, string defense_element, int offense_lv, int defense_lv)
{
    string vulnerable = "normal";

    if (offense_element == "Fire" && defense_element == "Water")
    {
        if (offense_lv < defense_lv)
            vulnerable = "normal";
        else
            vulnerable = "weak";
    }
    else if (offense_element == "Water" && defense_element == "Thunder")
    {
        if (offense_lv > defense_lv)
            vulnerable = "normal";
        else
            vulnerable = "weak";
    }
    else if (offense_element == "Thunder" && defense_element == "Earth")
    {
        if (offense_lv > defense_lv)
            vulnerable = "normal";
        else
            vulnerable = "weak";
    }
    else if (offense_element == "Earth" && defense_element == "Fire")
    {
        if (offense_lv > defense_lv)
            vulnerable = "normal";
        else
            vulnerable = "weak";
    }

    if (offense_element == "Water" && defense_element == "Fire")
    {
        if (offense_lv < defense_lv)
            vulnerable = "normal";
        else
            vulnerable = "strong";
    }
    else if (offense_element == "Fire" && defense_element == "Earth")
    {
        if (offense_lv < defense_lv)
            vulnerable = "normal";
        else
            vulnerable = "strong";
    }
    else if (offense_element == "Earth" && defense_element == "Thunder")
    {
        if (offense_lv < defense_lv)
            vulnerable = "normal";
        else
            vulnerable = "strong";
    }
    else if (offense_element == "Thunder" && defense_element == "Water")
    {
        if (offense_lv < defense_lv)
            vulnerable = "normal";
        else
            vulnerable = "strong";
    }
    return vulnerable;
}

string element ()
{
    int element_choice = 0;
    string element_type;

    srand(time(NULL));

    element_choice = rand() % 50;

    if (element_choice <= 10)
        element_type = "Fire";
    else if (element_choice <= 20)
        element_type = "Water";
    else if (element_choice <= 30)
        element_type = "Earth";
    else if (element_choice <= 40)
        element_type = "Thunder";
    else
        element_type = "";


    return element_type;
}

