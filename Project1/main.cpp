#include "raylib.h"
#include "Button.h"
#include "Theme.h"
#include "ScreenState.h"
#include "TextBox.h"

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

// =============================================================
// LANGUAGE SYSTEM
// =============================================================

enum class Language
{
    English = 0,
    Bulgarian,
    Spanish,
    French,
    German
};

struct Translations
{
    const char* appTitle;
    const char* loginSignup;
    const char* movies;
    const char* bookedSeats;
    const char* adminPanel;
    const char* settings;
    const char* exitBtn;
    const char* logout;
    const char* authentication;
    const char* login;
    const char* signUp;
    const char* back;
    const char* createAccount;
    const char* emailPlaceholder;
    const char* passwordPlaceholder;
    const char* verifyPasswordPlaceholder;
    const char* specialCodePlaceholder;
    const char* invalidCredentials;
    const char* chooseYourSeat;
    const char* screen;
    const char* confirmSelection;
    const char* yourBookedSeats;
    const char* noSeatsBooked;
    const char* booked;
    const char* seatLegendBook;
    const char* seatLegendView;
    const char* noSeatsSelected;
    const char* selected;
    const char* movieListTitle;
    const char* bookTickets;
    const char* description;
    const char* genre;
    const char* duration;
    const char* rating;
    const char* adminPanelTitle;
    const char* addMovie;
    const char* removeMovie;
    const char* movieTitle;
    const char* settingsTitle;
    const char* language;
    const char* fontSize;
    const char* fontSizeSmall;
    const char* fontSizeNormal;
    const char* fontSizeLarge;
    const char* successLoggedIn;
    const char* adminOnly;
    const char* mustLogin;
    const char* noMovies;
    const char* addMovieTitle;
    const char* addMovieGenre;
    const char* addMovieDuration;
    const char* addMovieRating;
    const char* addMovieDesc;
    const char* addBtn;
    const char* minutes;
    const char* stars;
};

static Translations LANG_EN = {
    "ONLINE CINEMA BOOKING SYSTEM",
    "Log in / Sign up",
    "Movies",
    "My Booked Seats",
    "Admin Panel",
    "Settings",
    "Exit",
    "Log Out",
    "Authentication",
    "Login",
    "Sign Up",
    "Back",
    "Create Account",
    "Email",
    "Password",
    "Verify Password",
    "Special Code (optional)",
    "Invalid email or password",
    "Choose Your Seat",
    "SCREEN",
    "Confirm Selection",
    "Your Booked Seats",
    "No seats booked yet",
    "Booked",
    "Red = booked  |  Green = your selection  |  Click to toggle",
    "Green = your booked seat",
    "No seats selected",
    "Selected: ",
    "Movie List",
    "Book Tickets",
    "Description",
    "Genre",
    "Duration",
    "Rating",
    "Admin Panel",
    "Add Movie",
    "Remove",
    "Title",
    "Settings",
    "Language",
    "Font Size",
    "Small",
    "Normal",
    "Large",
    "Successfully Logged In",
    "Admin access only",
    "Please log in first",
    "No movies available",
    "Title",
    "Genre",
    "Duration (min)",
    "Rating (1-10)",
    "Description",
    "Add",
    " min",
    "/10"
};

static Translations LANG_BG = {
    "SISTEMA ZA REZERVACII NA KINO",
    "Vlizane / Registraciya",
    "Filmi",
    "Moite Mesta",
    "Admin Panel",
    "Nastrojki",
    "Izход",
    "Izlizane",
    "Autentikaciya",
    "Vlizane",
    "Registraciya",
    "Nazad",
    "Sаzdаj Аkаunt",
    "Imejl",
    "Pаrolа",
    "Potvardi Parolata",
    "Specijalen Kod (opcionalen)",
    "Nevaliden imejl ili parolа",
    "Izberete Svoyto Myasto",
    "EKRAN",
    "Potvardi Izbora",
    "Vashite Rezervirani Mesta",
    "Nyama rezervirani mesta",
    "Rezervirani",
    "Cherveno = zaeto  |  Zeleno = vashe  |  Kliknete za promyana",
    "Zeleno = vashe rezervirano myasto",
    "Nyama izbrani mesta",
    "Izbrani: ",
    "Spisak s Filmi",
    "Rezerviraj Bileti",
    "Opisanie",
    "Zanr",
    "Prodaljitelnost",
    "Ocenka",
    "Admin Panel",
    "Dobavi Film",
    "Mahni",
    "Zaglavie",
    "Nastrojki",
    "Ezik",
    "Razmer na Shrifta",
    "Malak",
    "Normalen",
    "Golyam",
    "Uspeshno Vlizane",
    "Samo za administratori",
    "Molya vlezте parvo",
    "Nyama nalichni filmi",
    "Zaglavie",
    "Zanr",
    "Prodaljitelnost (min)",
    "Ocenka (1-10)",
    "Opisanie",
    "Dobavi",
    " min",
    "/10"
};

static Translations LANG_ES = {
    "SISTEMA DE RESERVAS DE CINE",
    "Iniciar / Registrarse",
    "Peliculas",
    "Mis Asientos",
    "Panel de Admin",
    "Configuracion",
    "Salir",
    "Cerrar Sesion",
    "Autenticacion",
    "Iniciar Sesion",
    "Registrarse",
    "Atras",
    "Crear Cuenta",
    "Correo",
    "Contrasena",
    "Verificar Contrasena",
    "Codigo Especial (opcional)",
    "Correo o contrasena invalidos",
    "Elige Tu Asiento",
    "PANTALLA",
    "Confirmar Seleccion",
    "Tus Asientos Reservados",
    "No hay asientos reservados",
    "Reservados",
    "Rojo = ocupado  |  Verde = tu seleccion  |  Clic para cambiar",
    "Verde = tu asiento reservado",
    "No hay asientos seleccionados",
    "Seleccionados: ",
    "Lista de Peliculas",
    "Reservar Entradas",
    "Descripcion",
    "Genero",
    "Duracion",
    "Puntuacion",
    "Panel de Admin",
    "Agregar Pelicula",
    "Eliminar",
    "Titulo",
    "Configuracion",
    "Idioma",
    "Tamano de Fuente",
    "Pequeno",
    "Normal",
    "Grande",
    "Sesion Iniciada",
    "Solo administradores",
    "Inicia sesion primero",
    "No hay peliculas disponibles",
    "Titulo",
    "Genero",
    "Duracion (min)",
    "Puntuacion (1-10)",
    "Descripcion",
    "Agregar",
    " min",
    "/10"
};

static Translations LANG_FR = {
    "SYSTEME DE RESERVATION DE CINEMA",
    "Se connecter / S'inscrire",
    "Films",
    "Mes Places",
    "Panneau Admin",
    "Parametres",
    "Quitter",
    "Deconnexion",
    "Authentification",
    "Connexion",
    "S'inscrire",
    "Retour",
    "Creer un Compte",
    "Email",
    "Mot de passe",
    "Verifier le mot de passe",
    "Code Special (optionnel)",
    "Email ou mot de passe invalide",
    "Choisissez Votre Place",
    "ECRAN",
    "Confirmer la Selection",
    "Vos Places Reservees",
    "Aucune place reservee",
    "Reserves",
    "Rouge = pris  |  Vert = votre choix  |  Clic pour basculer",
    "Vert = votre place reservee",
    "Aucune place selectionnee",
    "Selectionnes: ",
    "Liste des Films",
    "Reserver des Billets",
    "Description",
    "Genre",
    "Duree",
    "Note",
    "Panneau Admin",
    "Ajouter Film",
    "Supprimer",
    "Titre",
    "Parametres",
    "Langue",
    "Taille de Police",
    "Petite",
    "Normale",
    "Grande",
    "Connexion Reussie",
    "Acces administrateur uniquement",
    "Veuillez vous connecter",
    "Aucun film disponible",
    "Titre",
    "Genre",
    "Duree (min)",
    "Note (1-10)",
    "Description",
    "Ajouter",
    " min",
    "/10"
};

static Translations LANG_DE = {
    "ONLINE KINO BUCHUNGSSYSTEM",
    "Anmelden / Registrieren",
    "Filme",
    "Meine Sitze",
    "Admin-Panel",
    "Einstellungen",
    "Beenden",
    "Abmelden",
    "Authentifizierung",
    "Anmelden",
    "Registrieren",
    "Zuruck",
    "Konto erstellen",
    "E-Mail",
    "Passwort",
    "Passwort bestatigen",
    "Sondercode (optional)",
    "Ungultige E-Mail oder Passwort",
    "Wahlen Sie Ihren Sitz",
    "LEINWAND",
    "Auswahl bestatigen",
    "Ihre gebuchten Sitze",
    "Keine Sitze gebucht",
    "Gebucht",
    "Rot = belegt  |  Grun = Ihre Wahl  |  Klicken zum Umschalten",
    "Grun = Ihr gebuchter Sitz",
    "Keine Sitze ausgewahlt",
    "Ausgewahlt: ",
    "Filmliste",
    "Tickets buchen",
    "Beschreibung",
    "Genre",
    "Dauer",
    "Bewertung",
    "Admin-Panel",
    "Film hinzufugen",
    "Entfernen",
    "Titel",
    "Einstellungen",
    "Sprache",
    "Schriftgrosse",
    "Klein",
    "Normal",
    "Gros",
    "Erfolgreich angemeldet",
    "Nur fur Admins",
    "Bitte zuerst anmelden",
    "Keine Filme verfugbar",
    "Titel",
    "Genre",
    "Dauer (Min)",
    "Bewertung (1-10)",
    "Beschreibung",
    "Hinzufugen",
    " Min",
    "/10"
};

const Translations& GetTranslations(Language lang)
{
    switch (lang)
    {
    case Language::Bulgarian: return LANG_BG;
    case Language::Spanish:   return LANG_ES;
    case Language::French:    return LANG_FR;
    case Language::German:    return LANG_DE;
    default:                  return LANG_EN;
    }
}

// =============================================================
// DATA STRUCTURES
// =============================================================

struct UserAccount
{
    std::string email;
    std::string password;
    std::string seat;
    bool isAdmin;
    bool isBanned;
};

struct Movie
{
    std::string title;
    std::string genre;
    int durationMinutes;
    float rating;
    std::string description;
};

// =============================================================
// REMEMBERED LOGIN
// =============================================================

void SaveRemembered(const std::string& email, const std::string& password)
{
    std::ofstream file("remembered.txt");
    file << email << "|" << password << "\n";
    file.close();
}

void LoadRemembered(std::string& email, std::string& password)
{
    std::ifstream file("remembered.txt");
    if (!file.is_open()) return;
    std::string line;
    if (std::getline(file, line))
    {
        size_t sep = line.find('|');
        if (sep != std::string::npos)
        {
            email = line.substr(0, sep);
            password = line.substr(sep + 1);
        }
    }
    file.close();
}

// =============================================================
// USER FILE I/O
// =============================================================

std::vector<UserAccount> LoadUsers()
{
    std::vector<UserAccount> users;
    std::ifstream file("users.txt");
    std::string line;
    while (std::getline(file, line))
    {
        // format: email|password|seats|isAdmin|isBanned
        size_t s1 = line.find('|');
        if (s1 == std::string::npos) continue;
        size_t s2 = line.find('|', s1 + 1);
        size_t s3 = (s2 != std::string::npos) ? line.find('|', s2 + 1) : std::string::npos;
        size_t s4 = (s3 != std::string::npos) ? line.find('|', s3 + 1) : std::string::npos;

        UserAccount user;
        user.email = line.substr(0, s1);
        user.isAdmin = false;
        user.isBanned = false;

        if (s2 == std::string::npos)
        {
            user.password = line.substr(s1 + 1);
            user.seat = "";
        }
        else if (s3 == std::string::npos)
        {
            user.password = line.substr(s1 + 1, s2 - s1 - 1);
            std::string rest = line.substr(s2 + 1);
            if (rest == "1" || rest == "0")
            {
                user.seat = "";
                user.isAdmin = (rest == "1");
            }
            else
            {
                user.seat = rest;
            }
        }
        else if (s4 == std::string::npos)
        {
            user.password = line.substr(s1 + 1, s2 - s1 - 1);
            user.seat = line.substr(s2 + 1, s3 - s2 - 1);
            user.isAdmin = (line.substr(s3 + 1) == "1");
        }
        else
        {
            user.password = line.substr(s1 + 1, s2 - s1 - 1);
            user.seat = line.substr(s2 + 1, s3 - s2 - 1);
            user.isAdmin = (line.substr(s3 + 1, s4 - s3 - 1) == "1");
            user.isBanned = (line.substr(s4 + 1) == "1");
        }

        users.push_back(user);
    }
    file.close();
    return users;
}

void SaveUsers(const std::vector<UserAccount>& users)
{
    std::ofstream file("users.txt");
    for (const UserAccount& user : users)
    {
        file << user.email
            << "|" << user.password
            << "|" << user.seat
            << "|" << (user.isAdmin ? "1" : "0")
            << "|" << (user.isBanned ? "1" : "0")
            << "\n";
    }
    file.close();
}

// =============================================================
// MOVIE FILE I/O
// =============================================================

std::vector<Movie> LoadMovies()
{
    std::vector<Movie> movies;
    std::ifstream file("movies.txt");
    if (!file.is_open())
    {
        // Default movies if file doesn't exist
        movies.push_back({
            "Inception",
            "Sci-Fi / Thriller",
            148,
            9.0f,
            "A thief who steals corporate secrets through the use of dream-sharing technology is given the inverse task of planting an idea into the mind of a C.E.O. A visually stunning mind-bending masterpiece by Christopher Nolan."
            });
        movies.push_back({
            "The Dark Knight",
            "Action / Crime",
            152,
            9.0f,
            "When the menace known as the Joker wreaks havoc and chaos on the people of Gotham, Batman must accept one of the greatest psychological and physical tests of his ability to fight injustice. Heath Ledger delivers an iconic performance."
            });
        movies.push_back({
            "Interstellar",
            "Sci-Fi / Drama",
            169,
            8.6f,
            "A team of explorers travel through a wormhole in space in an attempt to ensure humanity's survival. A breathtaking journey through space and time directed by Christopher Nolan with stunning visuals and an emotional story."
            });
        movies.push_back({
            "Avengers: Endgame",
            "Action / Superhero",
            181,
            8.4f,
            "After the devastating events of Infinity War, the universe is in ruins. With the help of remaining allies, the Avengers assemble once more in order to reverse Thanos's actions and restore balance to the universe."
            });
        return movies;
    }

    std::string line;
    while (std::getline(file, line))
    {
        // format: title|genre|duration|rating|description
        size_t s1 = line.find('|');
        if (s1 == std::string::npos) continue;
        size_t s2 = line.find('|', s1 + 1);
        if (s2 == std::string::npos) continue;
        size_t s3 = line.find('|', s2 + 1);
        if (s3 == std::string::npos) continue;
        size_t s4 = line.find('|', s3 + 1);
        if (s4 == std::string::npos) continue;

        Movie m;
        m.title = line.substr(0, s1);
        m.genre = line.substr(s1 + 1, s2 - s1 - 1);
        m.durationMinutes = std::stoi(line.substr(s2 + 1, s3 - s2 - 1));
        m.rating = std::stof(line.substr(s3 + 1, s4 - s3 - 1));
        m.description = line.substr(s4 + 1);
        movies.push_back(m);
    }
    file.close();
    return movies;
}

void SaveMovies(const std::vector<Movie>& movies)
{
    std::ofstream file("movies.txt");
    for (const Movie& m : movies)
    {
        file << m.title
            << "|" << m.genre
            << "|" << m.durationMinutes
            << "|" << m.rating
            << "|" << m.description
            << "\n";
    }
    file.close();
}

// =============================================================
// BOOKING HELPERS  (per-movie, stored in bookings.txt)
// Format per line:  email|movieTitle|seat1,seat2,...
// =============================================================

struct Booking
{
    std::string email;
    std::string movieTitle;
    std::string seats; // comma-separated
};

std::vector<Booking> LoadBookings()
{
    std::vector<Booking> list;
    std::ifstream file("bookings.txt");
    if (!file.is_open()) return list;
    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        size_t p1 = line.find('|');
        if (p1 == std::string::npos) continue;
        size_t p2 = line.find('|', p1 + 1);
        if (p2 == std::string::npos) continue;
        Booking b;
        b.email = line.substr(0, p1);
        b.movieTitle = line.substr(p1 + 1, p2 - p1 - 1);
        b.seats = line.substr(p2 + 1);
        list.push_back(b);
    }
    return list;
}

void SaveBookings(const std::vector<Booking>& bookings)
{
    std::ofstream file("bookings.txt");
    for (const Booking& b : bookings)
        file << b.email << "|" << b.movieTitle << "|" << b.seats << "\n";
}

// Returns the comma-separated seat string for a specific user + movie
std::string GetSeatsForUserAndMovie(const std::string& email, const std::string& movieTitle)
{
    for (const Booking& b : LoadBookings())
        if (b.email == email && b.movieTitle == movieTitle)
            return b.seats;
    return "";
}

// Returns true if another user has already booked this seat for this movie
bool IsSeatTakenByAnotherUser(const std::string& seat,
    const std::string& movieTitle,
    const std::string& loggedInEmail)
{
    for (const Booking& b : LoadBookings())
    {
        if (b.email == loggedInEmail) continue;
        if (b.movieTitle != movieTitle) continue;
        std::stringstream ss(b.seats);
        std::string tok;
        while (std::getline(ss, tok, ','))
            if (tok == seat) return true;
    }
    return false;
}

// Upserts the seat string for a user+movie pair
void SaveSeatsForUserAndMovie(const std::string& email,
    const std::string& movieTitle,
    const std::string& seats)
{
    std::vector<Booking> bookings = LoadBookings();
    bool found = false;
    for (Booking& b : bookings)
    {
        if (b.email == email && b.movieTitle == movieTitle)
        {
            b.seats = seats;
            found = true;
            break;
        }
    }
    if (!found)
    {
        Booking nb;
        nb.email = email;
        nb.movieTitle = movieTitle;
        nb.seats = seats;
        bookings.push_back(nb);
    }
    SaveBookings(bookings);
}

// Deletes all booking records for a given user (used by Delete Account)
void DeleteBookingsForUser(const std::string& email)
{
    std::vector<Booking> bookings = LoadBookings();
    bookings.erase(
        std::remove_if(bookings.begin(), bookings.end(),
            [&](const Booking& b) { return b.email == email; }),
        bookings.end()
    );
    SaveBookings(bookings);
}

// =============================================================
// DRAW HELPERS
// =============================================================

void DrawCenteredText(const char* text, int y, int fontSize, Color color, int screenWidth)
{
    int w = MeasureText(text, fontSize);
    DrawText(text, screenWidth / 2 - w / 2, y, fontSize, color);
}

// =============================================================
// MAIN
// =============================================================

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1600, 900, "Cinema Booking System");
    SetWindowMinSize(1280, 720);
    MaximizeWindow();
    SetTargetFPS(60);

    // ----- App State -----
    bool darkMode = true;
    bool loginFailed = false;
    bool loginBanned = false;
    std::string loggedInEmail = "";
    bool isAdmin = false;
    std::vector<std::string> selectedSeats;
    ScreenState currentScreen = ScreenState::Home;
    ScreenState previousScreen = ScreenState::Home; // tracks last frame's screen
    ScreenState bookingFrom = ScreenState::Home;
    int selectedMovieIndex = -1;

    // ----- Language & Font -----
    Language currentLanguage = Language::English;
    float fontScale = 1.0f; // 0.8f = small, 1.0f = normal, 1.3f = large

    // ----- Movies -----
    std::vector<Movie> movies = LoadMovies();

    // ----- Remembered login -----
    std::string rememberedEmail = "";
    std::string rememberedPassword = "";
    LoadRemembered(rememberedEmail, rememberedPassword);

    // ----- Persistent Textboxes -----
    TextBox emailBox(0, 0, 400, 60);
    TextBox passwordBox(0, 0, 400, 60);
    TextBox confirmPasswordBox(0, 0, 400, 60);
    TextBox specialCodeBox(0, 0, 400, 60);
    int activeTextBoxIndex = 0;

    // Admin panel textboxes
    TextBox adminTitleBox(0, 0, 380, 50);
    TextBox adminGenreBox(0, 0, 380, 50);
    TextBox adminDurationBox(0, 0, 180, 50);
    TextBox adminRatingBox(0, 0, 180, 50);
    TextBox adminDescBox(0, 0, 780, 50);
    int adminActiveBox = 0;
    int adminTab = 0; // 0 = Movies, 1 = Users
    std::string adminMessage = "";

    while (!WindowShouldClose())
    {
        // Record which screen we were on at the START of this frame (before any transitions)
        previousScreen = currentScreen;

        int W = GetScreenWidth();
        int H = GetScreenHeight();

        const Translations& T = GetTranslations(currentLanguage);

        Theme currentTheme = darkMode ? DarkTheme : LightTheme;

        // Font sizes scaled
        int fs_title = (int)(42 * fontScale);
        int fs_body = (int)(28 * fontScale);
        int fs_small = (int)(22 * fontScale);
        int fs_tiny = (int)(18 * fontScale);

        // Panel dimensions
        const float panelW = 950.0f;
        const float panelH = 760.0f;
        float panelX = (W - panelW) / 2.0f;
        float panelY = (H - panelH) / 2.0f;

        // Standard button settings
        const float btnW = 500.0f;
        const float btnH = 70.0f;
        float btnX = W / 2.0f - btnW / 2.0f;

        // Textbox X
        float tbX = W / 2.0f - 200.0f;

        // Update textbox positions
        emailBox.SetPosition(tbX, panelY + 270);
        passwordBox.SetPosition(tbX, panelY + 370);
        confirmPasswordBox.SetPosition(tbX, panelY + 470);
        specialCodeBox.SetPosition(tbX, panelY + 570);

        // =====================
        // THEME BUTTON (top-right)
        // =====================
        Button themeButton(W - 250.0f, 20, 220, 48,
            darkMode ? "Light Mode" : "Dark Mode");

        if (themeButton.IsClicked())
            darkMode = !darkMode;


        // =====================
        // HOME SCREEN buttons
        // =====================
        float homeY = panelY + 90;

        Button loginButton(btnX, homeY, btnW, btnH,
            loggedInEmail.empty() ? T.loginSignup : loggedInEmail.c_str());
        Button moviesButton(btnX, homeY + 90, btnW, btnH, T.movies);
        Button bookedSeatsButton(btnX, homeY + 180, btnW, btnH, T.bookedSeats);
        Button adminButton(btnX, homeY + 270, btnW, btnH, T.adminPanel);
        Button settingsButton(btnX, homeY + 360, btnW, btnH, T.settings);
        Button exitButton(btnX, homeY + 450, btnW, btnH, T.exitBtn);

        // Back button
        Button backButton(30, 30, 130, 46, T.back);

        // Auth buttons
        Button authLoginBtn(W / 2 - 150, panelY + 280, 300, 65, T.login);
        Button signUpBtn(W / 2 - 150, panelY + 370, 300, 65, T.signUp);
        Button loginSubmitBtn(W / 2 - 150, panelY + 490, 300, 65, T.login);
        Button signUpSubmitBtn(W / 2 - 150, panelY + 650, 300, 65, T.createAccount);

        // =====================
        // EVENTS - HOME
        // =====================
        if (currentScreen == ScreenState::Home)
        {
            if (loginButton.IsClicked())
            {
                emailBox.Clear();
                passwordBox.Clear();
                confirmPasswordBox.Clear();
                specialCodeBox.Clear();
                // Pre-fill with remembered credentials
                if (!rememberedEmail.empty())
                {
                    // Can't set text directly since TextBox has no SetText,
                    // user can just type. Pre-fill via remembered flow is shown
                    // on the login screen as a note.
                }
                currentScreen = ScreenState::AuthMenu;
            }
            if (moviesButton.IsClicked())
                currentScreen = ScreenState::MovieList;
            if (bookedSeatsButton.IsClicked())
            {
                if (loggedInEmail.empty()) currentScreen = ScreenState::AuthMenu;
                else                       currentScreen = ScreenState::ViewBookedSeats;
            }
            if (adminButton.IsClicked())
            {
                if (loggedInEmail.empty())
                    currentScreen = ScreenState::AuthMenu;
                else if (!isAdmin)
                    ; // just don't enter, could show message
                else
                {
                    adminTitleBox.Clear();
                    adminGenreBox.Clear();
                    adminDurationBox.Clear();
                    adminRatingBox.Clear();
                    adminDescBox.Clear();
                    adminMessage = "";
                    currentScreen = ScreenState::AdminPanel;
                }
            }
            if (settingsButton.IsClicked())
                currentScreen = ScreenState::Settings;
            if (exitButton.IsClicked())
                break;
        }

        // =====================
        // EVENTS - AUTH MENU
        // =====================
        if (currentScreen == ScreenState::AuthMenu)
        {
            if (authLoginBtn.IsClicked())
            {
                emailBox.Clear();
                passwordBox.Clear();
                // Pre-fill email if remembered
                // (TextBox doesn't have SetText; we note this below)
                emailBox.SetActive(true);
                passwordBox.SetActive(false);
                activeTextBoxIndex = 0;
                loginFailed = false;
                currentScreen = ScreenState::Login;
            }
            if (signUpBtn.IsClicked())
            {
                emailBox.Clear();
                passwordBox.Clear();
                confirmPasswordBox.Clear();
                specialCodeBox.Clear();
                emailBox.SetActive(true);
                passwordBox.SetActive(false);
                confirmPasswordBox.SetActive(false);
                specialCodeBox.SetActive(false);
                activeTextBoxIndex = 0;
                currentScreen = ScreenState::SignUp;
            }
            if (backButton.IsClicked())
                currentScreen = ScreenState::Home;
        }

        // =====================
        // EVENTS - LOGIN
        // =====================
        if (currentScreen == ScreenState::Login)
        {
            emailBox.Update();
            passwordBox.Update();

            if (emailBox.IsActive())    activeTextBoxIndex = 0;
            else if (passwordBox.IsActive()) activeTextBoxIndex = 1;

            if (IsKeyPressed(KEY_TAB))
            {
                int dir = (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) ? -1 : 1;
                activeTextBoxIndex = (activeTextBoxIndex + dir + 2) % 2;
                emailBox.SetActive(activeTextBoxIndex == 0);
                passwordBox.SetActive(activeTextBoxIndex == 1);
            }

            if (IsKeyPressed(KEY_ENTER) || loginSubmitBtn.IsClicked())
            {
                std::vector<UserAccount> users = LoadUsers();
                bool success = false;
                loginBanned = false;
                for (const UserAccount& u : users)
                {
                    if (u.email == emailBox.GetText() && u.password == passwordBox.GetText())
                    {
                        if (u.isBanned)
                        {
                            loginBanned = true;
                            loginFailed = false;
                            break;
                        }
                        success = true;
                        loggedInEmail = u.email;
                        isAdmin = u.isAdmin;
                        selectedSeats.clear(); // loaded fresh per-movie when booking
                        break;
                    }
                }
                if (success)
                {
                    loginFailed = false;
                    loginBanned = false;
                    currentScreen = ScreenState::Home;
                }
                else if (!loginBanned)
                {
                    loginFailed = true;
                }
            }
            if (backButton.IsClicked())
            {
                emailBox.Clear();
                passwordBox.Clear();
                currentScreen = ScreenState::AuthMenu;
            }
        }

        // =====================
        // EVENTS - SIGN UP
        // =====================
        if (currentScreen == ScreenState::SignUp)
        {
            emailBox.Update();
            passwordBox.Update();
            confirmPasswordBox.Update();
            specialCodeBox.Update();

            if (emailBox.IsActive())            activeTextBoxIndex = 0;
            else if (passwordBox.IsActive())    activeTextBoxIndex = 1;
            else if (confirmPasswordBox.IsActive()) activeTextBoxIndex = 2;
            else if (specialCodeBox.IsActive()) activeTextBoxIndex = 3;

            if (IsKeyPressed(KEY_TAB))
            {
                int dir = (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) ? -1 : 1;
                activeTextBoxIndex = (activeTextBoxIndex + dir + 4) % 4;
                emailBox.SetActive(activeTextBoxIndex == 0);
                passwordBox.SetActive(activeTextBoxIndex == 1);
                confirmPasswordBox.SetActive(activeTextBoxIndex == 2);
                specialCodeBox.SetActive(activeTextBoxIndex == 3);
            }

            if (IsKeyPressed(KEY_ENTER) || signUpSubmitBtn.IsClicked())
            {
                if (passwordBox.GetText() == confirmPasswordBox.GetText() && !emailBox.GetText().empty())
                {
                    bool makeAdmin = (specialCodeBox.GetText() == "0000");
                    UserAccount newUser;
                    newUser.email = emailBox.GetText();
                    newUser.password = passwordBox.GetText();
                    newUser.seat = "";
                    newUser.isAdmin = makeAdmin;
                    newUser.isBanned = false;

                    std::vector<UserAccount> users = LoadUsers();
                    users.push_back(newUser);
                    SaveUsers(users);

                    emailBox.Clear();
                    passwordBox.Clear();
                    confirmPasswordBox.Clear();
                    specialCodeBox.Clear();
                    currentScreen = ScreenState::AuthMenu;
                }
            }
            if (backButton.IsClicked())
            {
                emailBox.Clear();
                passwordBox.Clear();
                confirmPasswordBox.Clear();
                specialCodeBox.Clear();
                currentScreen = ScreenState::AuthMenu;
            }
        }

        // =====================
        // EVENTS - MOVIE LIST
        // =====================
        if (currentScreen == ScreenState::MovieList)
        {
            if (backButton.IsClicked())
                currentScreen = ScreenState::Home;

            // Only detect movie row clicks if we were ALREADY on this screen
            // last frame — prevents same-frame click-through from the Home button
            if (previousScreen == ScreenState::MovieList)
            {
                float listStartY = panelY + 120.0f;
                float itemH = 80.0f;
                float itemGap = 12.0f;

                for (int i = 0; i < (int)movies.size(); i++)
                {
                    Rectangle row = {
                        panelX + 30,
                        listStartY + i * (itemH + itemGap),
                        panelW - 60,
                        itemH
                    };

                    if (CheckCollisionPointRec(GetMousePosition(), row) &&
                        IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        selectedMovieIndex = i;
                        currentScreen = ScreenState::MovieDetail;
                    }
                }
            }
        }

        // =====================
        // EVENTS - MOVIE DETAIL
        // =====================
        if (currentScreen == ScreenState::MovieDetail)
        {
            Button bookBtn(btnX, panelY + 680, btnW, 65, T.bookTickets);
            if (backButton.IsClicked())
                currentScreen = ScreenState::MovieList;
            if (bookBtn.IsClicked())
            {
                if (loggedInEmail.empty())
                    currentScreen = ScreenState::AuthMenu;
                else
                {
                    selectedSeats.clear();
                    std::string movieTitle = movies[selectedMovieIndex].title;
                    std::string seatStr = GetSeatsForUserAndMovie(loggedInEmail, movieTitle);
                    std::stringstream ss(seatStr);
                    std::string tok;
                    while (std::getline(ss, tok, ','))
                        if (!tok.empty()) selectedSeats.push_back(tok);
                    bookingFrom = ScreenState::MovieDetail;
                    currentScreen = ScreenState::BookTickets;
                }
            }
        }

        // =====================
        // EVENTS - BOOK TICKETS
        // =====================
        if (currentScreen == ScreenState::BookTickets)
        {
            const int rows = 6;
            const int columns = 10;
            const float seatSz = 56.0f;
            const float seatGap = 14.0f;
            const float aisleGap = 30.0f; // extra space between cols 3-4 and 7-8
            const float gridW = columns * seatSz + (columns - 1) * seatGap + 2 * aisleGap;
            const float gridX = W / 2.0f - gridW / 2.0f;
            const float gridY = panelY + 245.0f;

            // Returns the X of the left edge of a column, accounting for aisles
            auto seatColX = [&](int col) -> float {
                float x = gridX + col * (seatSz + seatGap);
                if (col >= 3) x += aisleGap;
                if (col >= 7) x += aisleGap;
                return x;
                };

            std::string currentMovieTitle =
                (selectedMovieIndex >= 0 && selectedMovieIndex < (int)movies.size())
                ? movies[selectedMovieIndex].title : "";

            Vector2 mouse = GetMousePosition();

            for (int row = 0; row < rows; row++)
            {
                for (int col = 0; col < columns; col++)
                {
                    std::string seat = std::string(1, (char)('A' + row)) + std::to_string(col + 1);
                    Rectangle seatBounds = {
                        seatColX(col),
                        gridY + row * (seatSz + seatGap),
                        seatSz, seatSz
                    };
                    bool isTaken = IsSeatTakenByAnotherUser(seat, currentMovieTitle, loggedInEmail);
                    if (!isTaken &&
                        CheckCollisionPointRec(mouse, seatBounds) &&
                        IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        auto it = std::find(selectedSeats.begin(), selectedSeats.end(), seat);
                        if (it != selectedSeats.end()) selectedSeats.erase(it);
                        else selectedSeats.push_back(seat);
                    }
                }
            }

            Button confirmBtn(W / 2 - 150, panelY + 760, 300, 60, T.confirmSelection);
            if (confirmBtn.IsClicked() || IsKeyPressed(KEY_ENTER))
            {
                std::string seatStr;
                for (int i = 0; i < (int)selectedSeats.size(); i++)
                {
                    if (i > 0) seatStr += ",";
                    seatStr += selectedSeats[i];
                }
                SaveSeatsForUserAndMovie(loggedInEmail, currentMovieTitle, seatStr);
                currentScreen = bookingFrom;
            }
            if (backButton.IsClicked())
                currentScreen = bookingFrom;
        }

        // =====================
        // EVENTS - VIEW BOOKED SEATS
        // =====================
        if (currentScreen == ScreenState::ViewBookedSeats)
        {
            if (backButton.IsClicked())
                currentScreen = ScreenState::Home;
        }

        // =====================
        // EVENTS - ADMIN PANEL
        // =====================
        if (currentScreen == ScreenState::AdminPanel)
        {
            if (backButton.IsClicked())
                currentScreen = ScreenState::Home;

            // Tab switching
            float tabBtnY = panelY + 95;
            Button moviesTabBtn(panelX + 40, tabBtnY, 180, 44, "Movies");
            Button usersTabBtn(panelX + 230, tabBtnY, 180, 44, "Users");
            if (moviesTabBtn.IsClicked()) { adminTab = 0; adminMessage = ""; }
            if (usersTabBtn.IsClicked()) { adminTab = 1; adminMessage = ""; }

            if (adminTab == 0) // ---- MOVIES TAB ----
            {
                // Layout constants with enough spacing to prevent overlap
                // Each row: label (20px) + 10px gap + textbox (52px) + 30px gap to next label
                //   total per row = 112px
                float aFormX = panelX + 40;
                float aRow0 = panelY + 168; // Title & Genre textboxes
                float aRow1 = aRow0 + 92;  // Duration & Rating textboxes
                float aRow2 = aRow1 + 92;  // Description textbox
                float aAddY = aRow2 + 82;  // Add button

                adminTitleBox.SetPosition(aFormX, aRow0);
                adminGenreBox.SetPosition(aFormX + 410, aRow0);
                adminDurationBox.SetPosition(aFormX, aRow1);
                adminRatingBox.SetPosition(aFormX + 210, aRow1);
                adminDescBox.SetPosition(aFormX, aRow2);

                adminTitleBox.Update();
                adminGenreBox.Update();
                adminDurationBox.Update();
                adminRatingBox.Update();
                adminDescBox.Update();

                if (adminTitleBox.IsActive())         adminActiveBox = 0;
                else if (adminGenreBox.IsActive())    adminActiveBox = 1;
                else if (adminDurationBox.IsActive()) adminActiveBox = 2;
                else if (adminRatingBox.IsActive())   adminActiveBox = 3;
                else if (adminDescBox.IsActive())     adminActiveBox = 4;

                if (IsKeyPressed(KEY_TAB))
                {
                    int dir = (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) ? -1 : 1;
                    adminActiveBox = (adminActiveBox + dir + 5) % 5;
                    adminTitleBox.SetActive(adminActiveBox == 0);
                    adminGenreBox.SetActive(adminActiveBox == 1);
                    adminDurationBox.SetActive(adminActiveBox == 2);
                    adminRatingBox.SetActive(adminActiveBox == 3);
                    adminDescBox.SetActive(adminActiveBox == 4);
                }

                Button addMovieBtn(aFormX, aAddY, 200, 50, T.addBtn);
                if (addMovieBtn.IsClicked())
                {
                    std::string title = adminTitleBox.GetText();
                    std::string genre = adminGenreBox.GetText();
                    std::string durStr = adminDurationBox.GetText();
                    std::string ratingStr = adminRatingBox.GetText();
                    std::string desc = adminDescBox.GetText();

                    if (!title.empty() && !genre.empty() && !durStr.empty() && !ratingStr.empty())
                    {
                        try {
                            Movie m;
                            m.title = title;
                            m.genre = genre;
                            m.durationMinutes = std::stoi(durStr);
                            m.rating = std::stof(ratingStr);
                            m.description = desc.empty() ? "No description available." : desc;
                            movies.push_back(m);
                            SaveMovies(movies);
                            adminTitleBox.Clear();
                            adminGenreBox.Clear();
                            adminDurationBox.Clear();
                            adminRatingBox.Clear();
                            adminDescBox.Clear();
                            adminMessage = "Movie added!";
                        }
                        catch (...) {
                            adminMessage = "Invalid duration or rating.";
                        }
                    }
                    else
                    {
                        adminMessage = "Fill in title, genre, duration and rating.";
                    }
                }

                float movieListY = aAddY + 66;
                for (int i = 0; i < (int)movies.size(); i++)
                {
                    Button removeBtn(panelX + panelW - 150, movieListY + i * 48, 120, 38, T.removeMovie);
                    if (removeBtn.IsClicked())
                    {
                        movies.erase(movies.begin() + i);
                        SaveMovies(movies);
                        adminMessage = "Movie removed!";
                        break;
                    }
                }
            }
            else // ---- USERS TAB ----
            {
                float userListY = panelY + 165;
                std::vector<UserAccount> users = LoadUsers();
                for (int i = 0; i < (int)users.size(); i++)
                {
                    float rowY = userListY + i * 54;
                    if (!users[i].isAdmin) // can only ban/unban regular users
                    {
                        if (users[i].isBanned)
                        {
                            Button unbanBtn(panelX + panelW - 160, rowY + 4, 130, 38, "Unban");
                            if (unbanBtn.IsClicked())
                            {
                                users[i].isBanned = false;
                                SaveUsers(users);
                                adminMessage = "User unbanned!";
                            }
                        }
                        else
                        {
                            Button banBtn(panelX + panelW - 160, rowY + 4, 130, 38, "Ban");
                            if (banBtn.IsClicked())
                            {
                                users[i].isBanned = true;
                                SaveUsers(users);
                                adminMessage = "User banned!";
                            }
                        }
                    }
                }
            }
        }

        // =====================
        // EVENTS - SETTINGS
        // =====================
        if (currentScreen == ScreenState::Settings)
        {
            if (backButton.IsClicked())
                currentScreen = ScreenState::Home;

            float sx = panelX + 60;
            float sy = panelY + 130;
            float bw = 180;
            float bh = 55;
            float gap = 14;

            // Language buttons
            Button btnEN(sx, sy + 60, bw, bh, "English");
            Button btnBG(sx + (bw + gap), sy + 60, bw, bh, "Bulgarian");
            Button btnES(sx + 2 * (bw + gap), sy + 60, bw, bh, "Espanol");
            Button btnFR(sx + 3 * (bw + gap), sy + 60, bw, bh, "Francais");
            Button btnDE(sx + 4 * (bw + gap), sy + 60, bw, bh, "Deutsch");

            if (btnEN.IsClicked()) currentLanguage = Language::English;
            if (btnBG.IsClicked()) currentLanguage = Language::Bulgarian;
            if (btnES.IsClicked()) currentLanguage = Language::Spanish;
            if (btnFR.IsClicked()) currentLanguage = Language::French;
            if (btnDE.IsClicked()) currentLanguage = Language::German;

            // Font size buttons
            Button btnSmall(sx, sy + 200, bw, bh, T.fontSizeSmall);
            Button btnNormal(sx + bw + gap, sy + 200, bw, bh, T.fontSizeNormal);
            Button btnLarge(sx + 2 * (bw + gap), sy + 200, bw, bh, T.fontSizeLarge);

            if (btnSmall.IsClicked())  fontScale = 0.8f;
            if (btnNormal.IsClicked()) fontScale = 1.0f;
            if (btnLarge.IsClicked())  fontScale = 1.3f;

            // Logout & Delete Account (only visible when logged in)
            if (!loggedInEmail.empty())
            {
                float acctY = sy + 350;
                Button settingsLogoutBtn(sx, acctY, 200, 58, T.logout);
                Button deleteAcctBtn(sx + 220, acctY, 240, 58, "Delete Account");

                if (settingsLogoutBtn.IsClicked())
                {
                    SaveRemembered(loggedInEmail, "");
                    rememberedEmail = loggedInEmail;
                    rememberedPassword = "";
                    loggedInEmail = "";
                    isAdmin = false;
                    selectedSeats.clear();
                    currentScreen = ScreenState::Home;
                }

                if (deleteAcctBtn.IsClicked())
                {
                    // Remove user record and all their bookings, then log out
                    std::vector<UserAccount> users = LoadUsers();
                    users.erase(
                        std::remove_if(users.begin(), users.end(),
                            [&](const UserAccount& u) { return u.email == loggedInEmail; }),
                        users.end()
                    );
                    SaveUsers(users);
                    DeleteBookingsForUser(loggedInEmail);
                    loggedInEmail = "";
                    isAdmin = false;
                    selectedSeats.clear();
                    currentScreen = ScreenState::Home;
                }
            }
        }

        // =============================================================
        // DRAWING
        // =============================================================
        BeginDrawing();
        ClearBackground(currentTheme.background);

        // Draw panel background
        DrawRectangleRounded({ panelX, panelY, panelW, panelH }, 0.03f, 10, currentTheme.panel);

        // =====================
        // DRAW - HOME
        // =====================
        if (currentScreen == ScreenState::Home)
        {
            DrawCenteredText(T.appTitle, (int)(panelY + 40), fs_title, currentTheme.accent, W);

            loginButton.Draw(currentTheme);
            moviesButton.Draw(currentTheme);
            bookedSeatsButton.Draw(currentTheme);

            // Admin button: only show clickable if admin
            if (isAdmin)
                adminButton.Draw(currentTheme);
            else
            {
                // Draw dimmed admin button
                DrawRectangleRounded(
                    { btnX, homeY + 270, btnW, btnH },
                    0.2f, 10,
                    Color{ 45, 45, 60, 180 }
                );
                int tw = MeasureText(T.adminPanel, fs_body);
                DrawText(T.adminPanel,
                    W / 2 - tw / 2, (int)(homeY + 270 + btnH / 2 - fs_body / 2),
                    fs_body, Color{ 100, 100, 120, 255 });

                if (!loggedInEmail.empty())
                {
                    const char* hint = T.adminOnly;
                    int hw = MeasureText(hint, fs_tiny);
                    DrawText(hint, W / 2 - hw / 2, (int)(homeY + 270 + btnH + 4),
                        fs_tiny, Color{ 160, 80, 80, 255 });
                }
            }

            settingsButton.Draw(currentTheme);
            exitButton.Draw(currentTheme);
        }

        // =====================
        // DRAW - AUTH MENU
        // =====================
        if (currentScreen == ScreenState::AuthMenu)
        {
            DrawCenteredText(T.authentication, (int)(panelY + 160), fs_title, currentTheme.accent, W);
            authLoginBtn.Draw(currentTheme);
            signUpBtn.Draw(currentTheme);
            backButton.Draw(currentTheme);
        }

        // =====================
        // DRAW - LOGIN
        // =====================
        if (currentScreen == ScreenState::Login)
        {
            DrawCenteredText(T.login, (int)(panelY + 170), fs_title, currentTheme.accent, W);

            // Show remembered email hint
            if (!rememberedEmail.empty())
            {
                std::string hint = "Last: " + rememberedEmail;
                int hw = MeasureText(hint.c_str(), fs_tiny);
                DrawText(hint.c_str(), W / 2 - hw / 2, (int)(panelY + 240), fs_tiny,
                    Color{ 120, 180, 255, 200 });
            }

            emailBox.Draw(T.emailPlaceholder);
            passwordBox.Draw(T.passwordPlaceholder, true);
            loginSubmitBtn.Draw(currentTheme);

            if (loginFailed)
            {
                int tw = MeasureText(T.invalidCredentials, fs_small);
                DrawText(T.invalidCredentials, W / 2 - tw / 2, (int)(panelY + 580), fs_small, RED);
            }
            if (loginBanned)
            {
                const char* banMsg = "This account has been banned.";
                int tw = MeasureText(banMsg, fs_small);
                DrawText(banMsg, W / 2 - tw / 2, (int)(panelY + 580), fs_small, Color{ 230, 80, 80, 255 });
            }

            backButton.Draw(currentTheme);
        }

        // =====================
        // DRAW - SIGN UP
        // =====================
        if (currentScreen == ScreenState::SignUp)
        {
            DrawCenteredText(T.createAccount, (int)(panelY + 160), fs_title, currentTheme.accent, W);

            // Show admin code hint
            {
                const char* hint = "Tip: Enter special code '0000' to get admin access";
                int hw = MeasureText(hint, fs_tiny);
                DrawText(hint, W / 2 - hw / 2, (int)(panelY + 228), fs_tiny,
                    Color{ 120, 180, 120, 200 });
            }

            emailBox.Draw(T.emailPlaceholder);
            passwordBox.Draw(T.passwordPlaceholder, true);
            confirmPasswordBox.Draw(T.verifyPasswordPlaceholder, true);
            specialCodeBox.Draw(T.specialCodePlaceholder, true);
            signUpSubmitBtn.Draw(currentTheme);
            backButton.Draw(currentTheme);
        }

        // =====================
        // DRAW - MOVIE LIST
        // =====================
        if (currentScreen == ScreenState::MovieList)
        {
            DrawCenteredText(T.movieListTitle, (int)(panelY + 50), fs_title, currentTheme.accent, W);
            backButton.Draw(currentTheme);

            float listStartY = panelY + 120.0f;
            float itemH = 80.0f;
            float itemGap = 12.0f;

            if (movies.empty())
            {
                DrawCenteredText(T.noMovies, (int)(panelY + 300), fs_body, currentTheme.text, W);
            }
            else
            {
                for (int i = 0; i < (int)movies.size(); i++)
                {
                    Rectangle row = {
                        panelX + 30,
                        listStartY + i * (itemH + itemGap),
                        panelW - 60,
                        itemH
                    };

                    bool hovered = CheckCollisionPointRec(GetMousePosition(), row);
                    Color rowColor = hovered ? currentTheme.buttonHover : currentTheme.button;

                    DrawRectangleRounded(row, 0.15f, 10, rowColor);

                    // Title
                    DrawText(movies[i].title.c_str(),
                        (int)(row.x + 20), (int)(row.y + 10), fs_body, currentTheme.text);

                    // Genre + duration + rating
                    std::string meta = movies[i].genre + "   "
                        + std::to_string(movies[i].durationMinutes) + T.minutes
                        + "   " + std::to_string((int)movies[i].rating) + T.stars;
                    DrawText(meta.c_str(),
                        (int)(row.x + 20), (int)(row.y + 48), fs_tiny,
                        Color{ 160, 200, 255, 255 });

                    // Arrow
                    DrawText(">", (int)(row.x + row.width - 35), (int)(row.y + 24), fs_body, currentTheme.accent);
                }
            }
        }

        // =====================
        // DRAW - MOVIE DETAIL
        // =====================
        if (currentScreen == ScreenState::MovieDetail && selectedMovieIndex >= 0 &&
            selectedMovieIndex < (int)movies.size())
        {
            const Movie& m = movies[selectedMovieIndex];

            DrawCenteredText(m.title.c_str(), (int)(panelY + 40), fs_title, currentTheme.accent, W);

            // Genre / Duration / Rating row
            std::string metaLine = m.genre
                + "     " + std::to_string(m.durationMinutes) + T.minutes
                + "     " + T.rating + ": " + std::to_string((int)(m.rating * 10) / 10) + T.stars;
            DrawCenteredText(metaLine.c_str(), (int)(panelY + 105), fs_small,
                Color{ 160, 200, 255, 255 }, W);

            // Separator
            DrawRectangleRounded({ panelX + 40, panelY + 140, panelW - 80, 3 }, 1.0f, 2,
                currentTheme.buttonHover);

            // Description label
            DrawText(T.description, (int)(panelX + 50), (int)(panelY + 160), fs_small,
                currentTheme.accent);

            // Description text - word-wrap manually
            std::string desc = m.description;
            float descX = panelX + 50;
            float descY = panelY + 200;
            float maxDescW = panelW - 100;
            int descFS = fs_small;

            // Simple word-wrap
            std::vector<std::string> words;
            std::stringstream ssDesc(desc);
            std::string word;
            while (ssDesc >> word) words.push_back(word);

            std::string currentLine;
            float lineY = descY;
            for (const std::string& w : words)
            {
                std::string testLine = currentLine.empty() ? w : currentLine + " " + w;
                if (MeasureText(testLine.c_str(), descFS) > (int)maxDescW)
                {
                    if (!currentLine.empty())
                    {
                        DrawText(currentLine.c_str(), (int)descX, (int)lineY, descFS, currentTheme.text);
                        lineY += descFS + 8;
                    }
                    currentLine = w;
                }
                else
                {
                    currentLine = testLine;
                }
            }
            if (!currentLine.empty())
                DrawText(currentLine.c_str(), (int)descX, (int)lineY, descFS, currentTheme.text);

            // Book Tickets button
            Button bookBtn(btnX, panelY + 680, btnW, 65, T.bookTickets);
            bookBtn.Draw(currentTheme);

            if (loggedInEmail.empty())
            {
                int hw = MeasureText(T.mustLogin, fs_tiny);
                DrawText(T.mustLogin, W / 2 - hw / 2, (int)(panelY + 750), fs_tiny,
                    Color{ 200, 160, 80, 255 });
            }

            backButton.Draw(currentTheme);
        }

        // =====================
        // DRAW - BOOK TICKETS
        // =====================
        if (currentScreen == ScreenState::BookTickets)
        {
            const int rows = 6;
            const int columns = 10;
            const float seatSz = 56.0f;
            const float seatGap = 14.0f;
            const float aisleGap = 30.0f;
            const float gridW = columns * seatSz + (columns - 1) * seatGap + 2 * aisleGap;
            const float gridX = W / 2.0f - gridW / 2.0f;
            const float gridY = panelY + 245.0f;

            auto seatColX = [&](int col) -> float {
                float x = gridX + col * (seatSz + seatGap);
                if (col >= 3) x += aisleGap;
                if (col >= 7) x += aisleGap;
                return x;
                };

            std::string currentMovieTitle =
                (selectedMovieIndex >= 0 && selectedMovieIndex < (int)movies.size())
                ? movies[selectedMovieIndex].title : "";

            // Show movie title
            if (bookingFrom == ScreenState::MovieDetail && !currentMovieTitle.empty())
            {
                DrawCenteredText(currentMovieTitle.c_str(), (int)(panelY + 30), fs_small,
                    Color{ 160, 200, 255, 255 }, W);
            }

            DrawCenteredText(T.chooseYourSeat, (int)(panelY + 70), fs_title, currentTheme.accent, W);

            // Screen bar
            DrawRectangleRounded({ W / 2.0f - 250, panelY + 155, 500, 28 }, 0.4f, 12, currentTheme.accent);
            DrawCenteredText(T.screen, (int)(panelY + 190), (int)(22 * fontScale), currentTheme.text, W);

            Vector2 mouse = GetMousePosition();

            for (int row = 0; row < rows; row++)
            {
                std::string rowLabel = std::string(1, (char)('A' + row));
                DrawText(rowLabel.c_str(),
                    (int)(gridX - 44), (int)(gridY + row * (seatSz + seatGap) + 16),
                    (int)(22 * fontScale), currentTheme.text);

                for (int col = 0; col < columns; col++)
                {
                    std::string seat = rowLabel + std::to_string(col + 1);
                    Rectangle seatBounds = {
                        seatColX(col),
                        gridY + row * (seatSz + seatGap),
                        seatSz, seatSz
                    };
                    bool isTaken = IsSeatTakenByAnotherUser(seat, currentMovieTitle, loggedInEmail);
                    bool isSelected = std::find(selectedSeats.begin(), selectedSeats.end(), seat) != selectedSeats.end();
                    bool isHovered = CheckCollisionPointRec(mouse, seatBounds);

                    Color seatColor = currentTheme.button;
                    if (isTaken)         seatColor = { 120, 55, 55, 255 };
                    else if (isSelected) seatColor = { 40, 170, 95, 255 };
                    else if (isHovered)  seatColor = currentTheme.buttonHover;

                    DrawRectangleRounded(seatBounds, 0.18f, 8, seatColor);
                    int tw = MeasureText(seat.c_str(), 20);
                    DrawText(seat.c_str(),
                        (int)(seatBounds.x + seatBounds.width / 2 - tw / 2),
                        (int)(seatBounds.y + seatBounds.height / 2 - 10),
                        20, currentTheme.text);
                }
            }

            std::string seatMsg = selectedSeats.empty()
                ? T.noSeatsSelected
                : (std::string(T.selected) + [&]() {
                std::string s;
                for (int i = 0; i < (int)selectedSeats.size(); i++)
                {
                    if (i > 0) s += ", "; s += selectedSeats[i];
                }
                return s;
                    }());

            DrawCenteredText(seatMsg.c_str(), (int)(panelY + 695), fs_tiny, currentTheme.text, W);
            DrawCenteredText(T.seatLegendBook, (int)(panelY + 720), fs_tiny, currentTheme.text, W);

            Button confirmBtn(W / 2 - 150, panelY + 760, 300, 60, T.confirmSelection);
            confirmBtn.Draw(currentTheme);
            backButton.Draw(currentTheme);
        }

        // =====================
        // DRAW - VIEW BOOKED SEATS
        // =====================
        if (currentScreen == ScreenState::ViewBookedSeats)
        {
            const int vbRows = 6;
            const int vbCols = 10;
            const float vbSz = 56.0f;
            const float vbGap = 14.0f;
            const float vbAisle = 30.0f;
            const float vbGridW = vbCols * vbSz + (vbCols - 1) * vbGap + 2 * vbAisle;
            const float vbX = W / 2.0f - vbGridW / 2.0f;
            const float vbY = panelY + 245.0f;

            auto vbColX = [&](int col) -> float {
                float x = vbX + col * (vbSz + vbGap);
                if (col >= 3) x += vbAisle;
                if (col >= 7) x += vbAisle;
                return x;
                };

            // Collect ALL booked seats for this user across every movie
            std::vector<std::string> bookedList;
            int totalSeatCount = 0;
            {
                std::vector<Booking> allBookings = LoadBookings();
                for (const Booking& b : allBookings)
                {
                    if (b.email != loggedInEmail) continue;
                    std::stringstream bss(b.seats);
                    std::string btoken;
                    while (std::getline(bss, btoken, ','))
                        if (!btoken.empty()) { bookedList.push_back(btoken); totalSeatCount++; }
                }
            }

            DrawCenteredText(T.yourBookedSeats, (int)(panelY + 70), fs_title, currentTheme.accent, W);

            DrawRectangleRounded({ W / 2.0f - 250, panelY + 155, 500, 28 }, 0.4f, 12, currentTheme.accent);
            DrawCenteredText(T.screen, (int)(panelY + 190), (int)(22 * fontScale), currentTheme.text, W);

            std::string countLabel = (totalSeatCount == 0)
                ? T.noSeatsBooked
                : (std::string(T.booked) + ": " + std::to_string(totalSeatCount) + " seat(s) across all movies");
            DrawCenteredText(countLabel.c_str(), (int)(vbY - 30), fs_small, currentTheme.text, W);

            for (int row = 0; row < vbRows; row++)
            {
                std::string rowLabel = std::string(1, (char)('A' + row));
                DrawText(rowLabel.c_str(),
                    (int)(vbX - 44), (int)(vbY + row * (vbSz + vbGap) + 16),
                    (int)(22 * fontScale), currentTheme.text);

                for (int col = 0; col < vbCols; col++)
                {
                    std::string seat = rowLabel + std::to_string(col + 1);
                    Rectangle seatBounds = {
                        vbColX(col),
                        vbY + row * (vbSz + vbGap),
                        vbSz, vbSz
                    };
                    bool isBooked = std::find(bookedList.begin(), bookedList.end(), seat) != bookedList.end();
                    Color seatColor = isBooked ? Color{ 40, 170, 95, 255 } : currentTheme.button;
                    DrawRectangleRounded(seatBounds, 0.18f, 8, seatColor);
                    int tw = MeasureText(seat.c_str(), 20);
                    DrawText(seat.c_str(),
                        (int)(seatBounds.x + seatBounds.width / 2 - tw / 2),
                        (int)(seatBounds.y + seatBounds.height / 2 - 10),
                        20, isBooked ? WHITE : currentTheme.text);
                }
            }

            DrawCenteredText(T.seatLegendView,
                (int)(vbY + vbRows * (vbSz + vbGap) + 10), fs_tiny, currentTheme.text, W);

            backButton.Draw(currentTheme);
        }

        // =====================
        // DRAW - ADMIN PANEL
        // =====================
        if (currentScreen == ScreenState::AdminPanel)
        {
            DrawCenteredText(T.adminPanelTitle, (int)(panelY + 48), fs_title, currentTheme.accent, W);

            // --- Tab buttons ---
            float tabBtnY = panelY + 95;
            Button moviesTabBtn(panelX + 40, tabBtnY, 180, 44, "Movies");
            Button usersTabBtn(panelX + 230, tabBtnY, 180, 44, "Users");
            moviesTabBtn.Draw(currentTheme);
            usersTabBtn.Draw(currentTheme);

            // Underline active tab
            float tabUnderX = (adminTab == 0) ? panelX + 40 : panelX + 230;
            DrawRectangle((int)tabUnderX, (int)(tabBtnY + 44), 180, 4, currentTheme.accent);

            // Horizontal separator
            DrawRectangle((int)panelX, (int)(tabBtnY + 52), (int)panelW, 2, currentTheme.buttonHover);

            if (!adminMessage.empty())
            {
                DrawCenteredText(adminMessage.c_str(), (int)(panelY + 148), fs_tiny,
                    Color{ 100, 220, 100, 255 }, W);
            }

            if (adminTab == 0) // ---- MOVIES TAB ----
            {
                float aFormX = panelX + 40;
                float aRow0 = panelY + 168;
                float aRow1 = aRow0 + 92;
                float aRow2 = aRow1 + 92;
                float aAddY = aRow2 + 82;

                // Reposition (must match event code)
                adminTitleBox.SetPosition(aFormX, aRow0);
                adminGenreBox.SetPosition(aFormX + 410, aRow0);
                adminDurationBox.SetPosition(aFormX, aRow1);
                adminRatingBox.SetPosition(aFormX + 210, aRow1);
                adminDescBox.SetPosition(aFormX, aRow2);

                // Labels sit 22px above their textbox, well separated from the one above
                DrawText(T.addMovieTitle, (int)aFormX, (int)(aRow0 - 22), fs_tiny, currentTheme.text);
                DrawText(T.addMovieGenre, (int)(aFormX + 410), (int)(aRow0 - 22), fs_tiny, currentTheme.text);
                DrawText(T.addMovieDuration, (int)aFormX, (int)(aRow1 - 22), fs_tiny, currentTheme.text);
                DrawText(T.addMovieRating, (int)(aFormX + 210), (int)(aRow1 - 22), fs_tiny, currentTheme.text);
                DrawText(T.addMovieDesc, (int)aFormX, (int)(aRow2 - 22), fs_tiny, currentTheme.text);

                adminTitleBox.Draw(T.addMovieTitle);
                adminGenreBox.Draw(T.addMovieGenre);
                adminDurationBox.Draw(T.addMovieDuration);
                adminRatingBox.Draw(T.addMovieRating);
                adminDescBox.Draw(T.addMovieDesc);

                Button addMovieBtn(aFormX, aAddY, 200, 50, T.addBtn);
                addMovieBtn.Draw(currentTheme);

                // Movie list
                float movieListY = aAddY + 66;
                DrawText(T.movieListTitle, (int)aFormX, (int)(movieListY - 22), fs_tiny, currentTheme.accent);

                if (movies.empty())
                {
                    DrawText(T.noMovies, (int)aFormX, (int)movieListY, fs_tiny, currentTheme.text);
                }
                else
                {
                    for (int i = 0; i < (int)movies.size(); i++)
                    {
                        float rowY = movieListY + i * 48;
                        DrawText(movies[i].title.c_str(), (int)aFormX, (int)(rowY + 8), fs_tiny, currentTheme.text);
                        Button removeBtn(panelX + panelW - 150, rowY, 120, 38, T.removeMovie);
                        removeBtn.Draw(currentTheme);
                    }
                }
            }
            else // ---- USERS TAB ----
            {
                float aFormX = panelX + 40;
                float userListY = panelY + 165;

                // Column headers
                DrawText("Email", (int)aFormX, (int)(userListY - 26), fs_tiny, currentTheme.accent);
                DrawText("Role", (int)(panelX + panelW - 340), (int)(userListY - 26), fs_tiny, currentTheme.accent);
                DrawText("Status", (int)(panelX + panelW - 240), (int)(userListY - 26), fs_tiny, currentTheme.accent);
                DrawText("Action", (int)(panelX + panelW - 160), (int)(userListY - 26), fs_tiny, currentTheme.accent);

                DrawRectangle((int)panelX, (int)(userListY - 4), (int)panelW, 2, currentTheme.buttonHover);

                std::vector<UserAccount> users = LoadUsers();

                if (users.empty())
                {
                    DrawText("No accounts yet.", (int)aFormX, (int)userListY, fs_tiny, currentTheme.text);
                }
                else
                {
                    for (int i = 0; i < (int)users.size(); i++)
                    {
                        float rowY = userListY + i * 54;

                        // Alternate row background
                        if (i % 2 == 0)
                        {
                            DrawRectangleRounded(
                                { panelX + 8, rowY - 4, panelW - 16, 48 },
                                0.1f, 6, Color{ 40, 40, 58, 180 }
                            );
                        }

                        // Email
                        DrawText(users[i].email.c_str(), (int)aFormX, (int)(rowY + 10), fs_tiny, currentTheme.text);

                        // Role badge
                        const char* roleText = users[i].isAdmin ? "Admin" : "User";
                        Color roleColor = users[i].isAdmin
                            ? Color{ 100, 180, 255, 255 }
                        : Color{ 160, 160, 180, 255 };
                        DrawText(roleText, (int)(panelX + panelW - 340), (int)(rowY + 10), fs_tiny, roleColor);

                        // Status
                        const char* statusText = users[i].isBanned ? "Banned" : "Active";
                        Color statusColor = users[i].isBanned
                            ? Color{ 220, 80, 80, 255 }
                        : Color{ 80, 200, 80, 255 };
                        DrawText(statusText, (int)(panelX + panelW - 240), (int)(rowY + 10), fs_tiny, statusColor);

                        // Ban / Unban button (only for regular users)
                        if (!users[i].isAdmin)
                        {
                            if (users[i].isBanned)
                            {
                                Button unbanBtn(panelX + panelW - 160, rowY + 4, 130, 38, "Unban");
                                unbanBtn.Draw(currentTheme);
                            }
                            else
                            {
                                Button banBtn(panelX + panelW - 160, rowY + 4, 130, 38, "Ban");
                                banBtn.Draw(currentTheme);
                            }
                        }
                        else
                        {
                            // Show "Protected" for admins
                            DrawText("Protected", (int)(panelX + panelW - 155), (int)(rowY + 12),
                                fs_tiny, Color{ 100, 100, 120, 255 });
                        }
                    }
                }
            }

            backButton.Draw(currentTheme);
        }

        // =====================
        // DRAW - SETTINGS
        // =====================
        if (currentScreen == ScreenState::Settings)
        {
            DrawCenteredText(T.settingsTitle, (int)(panelY + 50), fs_title, currentTheme.accent, W);

            float sx = panelX + 60;
            float sy = panelY + 130;
            float bw = 170;
            float bh = 55;
            float gap = 12;

            // Language section
            DrawText(T.language, (int)sx, (int)sy, fs_body, currentTheme.text);

            Button btnEN(sx, sy + 50, bw, bh, "English");
            Button btnBG(sx + (bw + gap), sy + 50, bw, bh, "Bulgarian");
            Button btnES(sx + 2 * (bw + gap), sy + 50, bw, bh, "Espanol");
            Button btnFR(sx + 3 * (bw + gap), sy + 50, bw, bh, "Francais");
            Button btnDE(sx + 4 * (bw + gap), sy + 50, bw, bh, "Deutsch");

            // Highlight selected language
            auto drawLangBtn = [&](Button& btn, Language lang) {
                btn.Draw(currentTheme);
                if (currentLanguage == lang)
                {
                    DrawRectangleRounded(
                        { sx + (lang == Language::English ? 0 : lang == Language::Bulgarian ? bw + gap :
                               lang == Language::Spanish ? 2 * (bw + gap) : lang == Language::French ? 3 * (bw + gap) : 4 * (bw + gap)),
                         sy + 50, bw, bh },
                        0.2f, 10,
                        Color{ 0, 180, 255, 60 }
                    );
                }
                };

            btnEN.Draw(currentTheme);
            btnBG.Draw(currentTheme);
            btnES.Draw(currentTheme);
            btnFR.Draw(currentTheme);
            btnDE.Draw(currentTheme);

            // Active language indicator (underline)
            float selX = sx;
            if (currentLanguage == Language::Bulgarian) selX = sx + (bw + gap);
            else if (currentLanguage == Language::Spanish)  selX = sx + 2 * (bw + gap);
            else if (currentLanguage == Language::French)   selX = sx + 3 * (bw + gap);
            else if (currentLanguage == Language::German)   selX = sx + 4 * (bw + gap);

            DrawRectangle((int)selX, (int)(sy + 50 + bh + 2), (int)bw, 4, currentTheme.accent);

            // Font size section
            DrawText(T.fontSize, (int)sx, (int)(sy + 160), fs_body, currentTheme.text);

            Button btnSmall(sx, sy + 210, bw, bh, T.fontSizeSmall);
            Button btnNormal(sx + bw + gap, sy + 210, bw, bh, T.fontSizeNormal);
            Button btnLarge(sx + 2 * (bw + gap), sy + 210, bw, bh, T.fontSizeLarge);

            btnSmall.Draw(currentTheme);
            btnNormal.Draw(currentTheme);
            btnLarge.Draw(currentTheme);

            // Active font size indicator
            float fsSelX = sx;
            if (fontScale > 1.1f)      fsSelX = sx + 2 * (bw + gap);
            else if (fontScale > 0.9f) fsSelX = sx + bw + gap;

            DrawRectangle((int)fsSelX, (int)(sy + 210 + bh + 2), (int)bw, 4, currentTheme.accent);

            // Preview text
            const char* preview = "Preview text size";
            DrawCenteredText(preview, (int)(sy + 310), fs_body, currentTheme.text, W);

            // Account section — logout & delete account (when logged in)
            if (!loggedInEmail.empty())
            {
                float acctY = sy + 350;
                DrawText("Account", (int)sx, (int)(acctY - 26), fs_body, currentTheme.text);
                DrawRectangle((int)sx, (int)(acctY - 4), 460, 2, currentTheme.buttonHover);

                Button settingsLogoutBtn(sx, acctY, 200, 58, T.logout);
                Button deleteAcctBtn(sx + 220, acctY, 240, 58, "Delete Account");
                settingsLogoutBtn.Draw(currentTheme);
                deleteAcctBtn.Draw(currentTheme);

                DrawText("Permanently removes your account and all bookings",
                    (int)sx, (int)(acctY + 66), fs_tiny, Color{ 160, 80, 80, 220 });
            }

            backButton.Draw(currentTheme);
        }

        // =====================
        // ALWAYS: Theme button (top-right)
        // =====================
        themeButton.Draw(currentTheme);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
