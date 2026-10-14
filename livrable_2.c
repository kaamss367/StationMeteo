#define nb_capteurs 5
 
#define capteur_press_atm 0
#define capteur_temp_air 1
#define capteur_hyg 2
#define capteur_gps 3
#define capteur_lum 4
 
#define indice_max 10
 
int tab_mesures[nb_capteurs];
bool tab_erreurs[nb_capteurs];
int tab_moy_instant[nb_capteurs];
 
int tab_capteur[nb_capteurs][indice_max];
 
int mesure_capteur;
int16_t erreur_mesure = -999;
int total[nb_capteurs];
uint8_t indice[nb_capteurs];
 
SDLogger_Init(&hspi1, SD_CS_GPIO_Port, SD_CS_Pin); //fonction qui initialise la carte SD.
GroveLight_Init(&hadc1); //fonction qui initialise le capteur de luminosité.
GroveGPS_Init(&huart1); //fonction qui initialise le GPS.
GroveRTC_Init(&hi2c1); //fonction qui initialise le module RTC.
 
void lecture_capteur();
GroveRTC_GetDateTime(&date_time); //fonction qui récupère la date et l’heure.
GroveGPS_Read(gps_data, sizeof(gps_data),1000U); //fonction qui lit les données GPS.
GroveLight_ReadRaw(&light_value); //fonction qui lit la valeur brute de luminosité.
 
int moy_gliss(int num_capteur, int mesure_capteur);
void maj_mesures(int tableau[], bool erreur[]);
 
void lire_gps(void);
void ecrire_sd(uint8_t num_capteur, int moyenne);
SDLogger_WriteLine("datalog.txt", data_line); //fonction qui écrit une ligne dans le fichier sur la carte SD.
 
uint32_t log_interval = 10;
uint32_t timeout = 30;
uint32_t file_max_size = 2; //ko;
 
bool lumin_active = true;
uint16_t lumin_low = 255;
uint16_t lumin_high = 768;
 
bool temp_air_active = true;
int16_t min_temp_air = -10;
int16_t max_temp_air = 60;
 
bool hygr_active = true;
int16_t hygr_mint = 0;
int16_t hygr_maxt = 50;
 
bool pressure_active = true;
uint16_t pressure_min = 850;
uint16_t pressure_max = 1080;
 
typedef struct
{
    uint8_t heure;
    uint8_t minute;
    uint8_t seconde;
} Clock;
 
typedef struct
{
    uint8_t jour;
    uint8_t mois;
    uint16_t annee;
} Date;
 
 
void mode_standard(void);
 
 
void mode_configuration(void); //file_max_size = 4 //ko;
 
 
void mode_maintenance(void);
void mode_economique(void);
 
 