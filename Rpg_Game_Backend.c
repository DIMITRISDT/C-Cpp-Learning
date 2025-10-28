#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char *name; // name of the character
    enum // the type of the character 
    {
        Warrior = 1,
        Mage = 2,
        Rogue = 3       
    } type;
    int HP; // Player's life
    int Mana; // Player's energy
    int Level; // Player's level
    char **inventory;  // equipment of the player
    int Item_Count; //the ammount of items the User's player has.
} Player;


//add a User's Character.
void CreateCharacter(Player *Pl, int i){
    // Memory allocation
    Pl[i].name = malloc(50*sizeof(char)); //string for char memory allocation
    if(Pl[i].name == NULL) { //error allocation
        printf("Error, malloc for char failed");
    }
    printf("-_-_Add A Player_-_-\n");
    //name
    printf("Type your name : ");
    scanf("%49s", Pl[i].name);
    getchar(); // removes the useless "\n"

    //type must be 1,2 or 3
    do {
    printf("Select your type (Warrior=1, Mage=2, Rogue=3) : ");
    scanf("%d", &Pl[i].type);
    }while(Pl[i].type != 1 && Pl[i].type != 2 && Pl[i].type != 3);

    //HP must be from 1-1000
    do {
        printf("Type your Character's hp (1-1000) : "); 
        scanf("%d", &Pl[i].HP);
    }while(Pl[i].HP < 1 || Pl[i].HP>1000);

    //Mana
    do{
        printf("Type your Character's mana (1-500) : ");
        scanf("%d", &Pl[i].Mana);
    }while(Pl[i].Mana < 1 || Pl[i].Mana > 500);
    
    //Level
    do{
        printf("Enter your Character's level (0-100): ");
        scanf("%d", &Pl[i].Level);
    } while (Pl[i].Level < 0 || Pl[i].Level > 100);
    
    
    //inventory set to empty
    Pl[i].inventory = NULL; //allocation is to null because the inventory is empty.
    Pl[i].Item_Count = 0; //0 because User's player does not have items.

    printf("\n_Player successfully created!!!\n");
}
//add stuff to the User's Character.
void AddItem(Player *Pl, int position){ //position is the number of the last placed character.
    if (Pl[position].Item_Count == 0) { //checks if in this address the item count is 0
        Pl[position].inventory = malloc(1*sizeof(char*)); //allocate memory 1 slot of char pointer memory.
        if(Pl[position].inventory == NULL) { //error allocation
            printf("Error, malloc for inventory failed.");
        }
    }
    else {
        Pl[position].inventory = realloc(Pl[position].inventory, (Pl[position].Item_Count+1)*sizeof(char*));
        if(Pl[position].inventory == NULL) { //error allocation
            printf("Error, realloc for inventory failed.");
        }
    }
    //allocate
    Pl[position].inventory[Pl[position].Item_Count]=malloc(50*sizeof(char)); //in the slot i created i allocate the size of the char memory.
    if(Pl[position].inventory[Pl[position].Item_Count] == NULL) { //error allocation
        printf("Error, malloc for char in the inventory failed.");
    }

    //add an item
    printf("Type the item's name to add it in your inventory : ");
    scanf("%49s", *(Pl[position].inventory+Pl[position].Item_Count));

    //message
    printf("\nYou're successfully added an item in your Player's inventory!!!\n");;

    //rise of item counter
    Pl[position].Item_Count++; //rise the counter +1 for the next adjustment of the inventory
}
//Display all Characters 
void DisplayCharacter(Player *Pl, int position) {
    printf("\n-[Name] : %s\n",Pl[position].name); //print the name
    if(Pl[position].type == 1){ //print the type
        printf("-[Type] : %s\n", "Warrior");
    }
    else if(Pl[position].type== 2){
        printf("-[Type] : %s\n", "Mage");
    }
    else {
        printf("-[Type] : %s\n", "Rogue");
    }
    printf("-[HP] : %d\n", Pl[position].HP); //print the hp
    printf("-[Mana] : %d\n", Pl[position].Mana); //print the mana
    printf("-[Level] : %d\n", Pl[position].Level); //print the level
    printf("-Inventory : ");
    printf("[");
    for(int j = 0; j<Pl[position].Item_Count; j++){
        printf("|%s|,", Pl[position].inventory[j]);

    }
    printf("]\n");
}
//Average Hp or Level
int Average(Player *Pl, int number_of_characters, int type){
    int i,sumforHp= 0, sumforLevel = 0; //sum0 for Hp and sum1 for Level
    for(i=0; i<number_of_characters; i++){
        sumforHp+= Pl[i].HP;
        sumforLevel+= Pl[i].Level;
    }
    //returns
    if(type == 0) { //HP
        return sumforHp/number_of_characters;
    }
    else if(type == 1){ //LEvel
        return sumforLevel/number_of_characters;
    }
}
//Search for a player
void SearchForCharacter(Player *Pl, int numberofCharacters){
    char character_name[50];
    bool character_found = false;
    printf("Enter the name of the Character you are looking for : ");
    fgets(character_name, 50, stdin);
    character_name[strcspn(character_name, "\n")] = '\0'; //removes the \n
    for(int i =0; i <numberofCharacters; i++){
        if(strcmp(character_name,Pl[i].name) == 0){ //if the character is found
            printf("\n Character found!\n");
            DisplayCharacter(Pl, i);
            character_found = true;
            break;
        }
    }
    if(!character_found){ //if the character is not found
        printf("\nCharacter with the name : %49s is not found.\n", character_name);
    }
}


int main() {
    int choice; // choice
    int characters = 0;
    char name[50];
    

    //dynamic array for struct
    Player *Pl= NULL; // Struct creation with pointer reference , NULL because its empty. 
    Player *temp;
    system("cls");
    do{

        printf("\n-------{Menu}-------\n");
        printf("1. Create a new character\n");
        printf("2. Add item to a character\n");
        printf("3. Display all characters\n");
        printf("4. Search character\n");
        printf("5. Character stats average (HP / Level)\n");
        printf("6. Exit\n");
        
        printf("Type you answer : ");
        scanf("%d", &choice);
        while(getchar() != '\n');
        switch (choice)
        {
        case 1:
            characters++;
            temp= realloc(Pl,characters*sizeof(Player));
            if(temp == NULL){ // error allocation
                printf("Error, realloc for struct failed.");
            }
            Pl = temp;
            CreateCharacter(Pl,characters-1); //Function for player's Creation.
            break;
        case 2:
            if (characters == 0){
                printf("\nYou must create a character to adjust his inventory!\n");
            }
            else{
                //position keep
                int position_of_Character = 0;
                bool Characterfound = false;
                printf("Enter the name of the Character you want to adjust the inventory :");
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = '\0'; //removes the \n
                for(int i=0; i< characters; i++){
                    if(strcmp(name,Pl[i].name)==0){
                        printf("Character found...\n");
                        position_of_Character = i;
                        Characterfound = true;
                        break;
                    }
                }
                if(Characterfound){
                    AddItem(Pl, position_of_Character);
                }
                else{
                    printf("\nCharacter with the name %s, is not found\n", name);
                }
            }
            break;
        case 3:
            if(characters == 0){
                printf("\nNo characters exist, please add one character at least to display.\n");
            }
            else{
                printf("\n_____[All Characters]_____\n");
                for(int i=0; i < characters; i++){
                    printf("_Player_ %d", i+1);
                    DisplayCharacter(Pl, i);
                }
            }
            break;
        case 4:
            if(characters == 0){
                printf("\nNo characters have been found.\n");
            }
            else{
                SearchForCharacter(Pl, characters);
            }
            
            break;
        case 5:
            //Average Hp and Levels
            if(characters == 0){ //only if at least one character created will print the output.
                printf("\nNo characters exist, please create a character in order to be able to see the calculations.\n");
            }
            else {
                printf("\nAverage Hp is : %d\n", Average(Pl, characters, 0));
                printf("Average Level is : %d\n", Average(Pl, characters, 1));
            }
            break;
        case 6:
            printf("Exiting...");
            break;
        default:
            printf("Invalid choice please choose beween 1-6.");
            break;
        }

    }while(choice != 6);

    //free memory allocations:
    for (int i = 0; i < characters; i++) {
        free(Pl[i].name);
        for(int j = 0; j < Pl[i].Item_Count; j++){
            free(Pl[i].inventory[j]); //free each thing inside the inventory 
        }
        free(Pl[i].inventory); //free each inventory
    }
    free(Pl);
    
    return 0;
}
