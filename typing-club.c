#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>

// ANSI 이스케이프 시퀀스
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m" // 터미널 기본 색상
#define ANSI_COLOR_GREEN "\x1b[32m"

// 구조체 정의
struct TypingSession
{
    time_t start_time;
    time_t end_time;
    int numMisCnt;
    int characters_typed;
};

void startpage(void)
{
    printf("+ ==================================================== +\n");
    printf("│                                                      │\n");
    printf("│                    LET'S PRACTICE                    │\n");
    printf("│                        TYPING                        │\n");
    printf("│                                                      │\n");
    printf("│                 PRESS  ENTER TO START                │\n");
    printf("│                     PRESS 0 TO END                   │\n");
    printf("│                                                      │\n");
    printf("+ ==================================================== +\n");
}

// Mac에서 getch() 이용
int getch(void)
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(0, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(0, TCSANOW, &oldt);
    return ch;
}

const char *englishSentences[] = {
    "The quick brown fox jumps over the lazy dog.",
    "Practice makes perfect.",
    "Coding is fun.",
    "Hello, World!",
    "The sun is shining brightly.",
    "I love programming.",
    "C programming is powerful.",
    "Learning a new language is exciting.",
    "The Internet is a vast resource of information.",
    "Computers have revolutionized the world.",
    "Life is like a box of chocolates.",
    "Knowledge is power.",
    "Where there's a will, there's a way.",
    "Actions speak louder than words.",
    "To be or not to be, that is the question.",
    "The early bird catches the worm.",
    "Every cloud has a silver lining.",
    "The pen is mightier than the sword.",
    "A picture is worth a thousand words.",
    "You can't judge a book by its cover.",
    "Don't cry over spilled milk.",
    "Easy come, easy go.",
    "Every dog has its day.",
    "Beauty is in the eye of the beholder.",
    "The best things in life are free.",
    "The world is your oyster.",
    "Laughter is the best medicine.",
    "When in Rome, do as the Romans do.",
    "Where there is smoke, there is fire.",
    "When the going gets tough, the tough get going.",
    "Two heads are better than one.",
    "A rolling stone gathers no moss.",
    "Honesty is the best policy.",
    "An apple a day keeps the doctor away.",
    "A watched pot never boils.",
    "Birds of a feather flock together.",
    "Don't put all your eggs in one basket.",
    "Actions speak louder than words.",
    "The early bird catches the worm.",
    "Don't count your chickens before they hatch.",
    "Necessity is the mother of invention.",
    "The grass is always greener on the other side.",
    "Out of sight, out of mind.",
    "You can't make an omelet without breaking eggs.",
    "Rome wasn't built in a day.",
    "A friend in need is a friend indeed.",
    "Better late than never.",
    "If the shoe fits, wear it.",
    "The more, the merrier.",
    "When in doubt, do without.",
    "Actions speak louder than words.",
    "Where there's smoke, there's fire.",
    "Too many cooks spoil the broth.",
    "Absence makes the heart grow fonder.",
    "The squeaky wheel gets the grease.",
    "If the cap fits, wear it.",
    "Don't put all your eggs in one basket.",
    "Where there's a will, there's a way.",
    "Where there's muck, there's brass.",
    "All that glitters is not gold.",
    "You can't make an omelet without breaking eggs.",
    "You can't teach an old dog new tricks.",
    "Beauty is in the eye of the beholder.",
    "You can't judge a book by its cover.",
    "Every dog has its day.",
    "The devil is in the details.",
    "A leopard can't change its spots.",
    "Actions speak louder than words.",
    "Don't count your chickens before they hatch.",
    "Necessity is the mother of invention.",
    "The grass is always greener on the other side.",
    "Out of sight, out of mind.",
    "You can't make an omelet without breaking eggs.",
    "Life is either a daring adventure or nothing at all",
    "The goal of life is living in agreement with nature.",
    "Only I can change me life, no one can do it for me.",
    "Your goal is to find your path, not to reach the top.",
    "Despite the forecast, live like it’s spring.",
    "Turn your wounds into wisdom.",
    "Great minds have purposes, others have wishes.",
    "No great man ever complains of want of opportunity.",
    "A day without laughter is a day wasted.",
    "All progress takes place outside the comfort zone.",
    "It is kind of fun to do the impossible.",
    "The less their ability, the more their conceit.",
    "No one is you and that is your power.",
    "Sometimes the right path is not the easiest one.",
    "Tough times never last, but tough people do.",
    "Grind Hard, Shine Hard.",
    "It hurt because it mattered.",
    "You will never know until you try.",
};

int main()
{
    startpage();

    char startinput = getch();
    if (startinput == '\n')
    {
        srand(time(NULL));
        while (1)
        {
            struct TypingSession session;
            session.numMisCnt = 0;

            int numEnglishSentences = sizeof(englishSentences) / sizeof(englishSentences[0]);
            int randomIndex = rand() % numEnglishSentences;
            const char *originalSentence = englishSentences[randomIndex];
            printf("  %s\n", originalSentence);

            int sentenceLength = strlen(originalSentence);
            session.start_time = time(NULL); // 시작 시간 기록

            printf("  ");
            for (int cursor = 0; cursor < sentenceLength; ++cursor)
            {
                char input = getch();

                if (!((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z') ||
                      input == ' ' || input == '.' || input == '\'' || input == ',' || input == '\n' || input == '0'))
                {
                    cursor -= 1;
                    continue;
                }

                if (input == '\n')
                    break;

                if (input == '0') // '0' 입력 시 프로그램 종료
                {
                    printf(ANSI_COLOR_GREEN"\n\n이용해 주셔서 감사합니다.\n"ANSI_COLOR_RESET);
                    return 0;
                }

                if (originalSentence[cursor] == input)
                {
                    printf(ANSI_COLOR_GREEN);
                }
                else
                {
                    printf(ANSI_COLOR_RED);
                    session.numMisCnt += 1;
                }
                printf("%c", input);
            }

            session.end_time = time(NULL);                                 // 끝 시간 기록
            session.characters_typed = sentenceLength - session.numMisCnt; // 올바르게 입력된 글자 수

            double elapsed_time = difftime(session.end_time, session.start_time); // 경과 시간 계산

            double characters_per_minute = (session.characters_typed) / (elapsed_time / 60.0); // 평균 타수 계산

            char enterInput;
            while (enterInput != '\n')
                enterInput = getch();
            printf("\n");
            printf(ANSI_COLOR_RESET);
            printf("  틀린 횟수: %d\n", session.numMisCnt);
            printf("  분당 타수: %.2f\n\n", characters_per_minute);
        }
    }

    return 0;
}