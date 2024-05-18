#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h> 

const char *positive_words[] = {"good", "happy", "great", "excellent", "awesome",
    "love", "joy", "happiness", "peace", "hope",
    "serenity", "laughter", "fun", "excitement", 
    "passion", "gratitude", "appreciation", "kindness",
    "compassion", "empathy", "generosity", "abundance",
    "prosperity", "success", "achievement", "accomplishment",
    "fulfillment", "satisfaction", "contentment", "bliss",
    "euphoria", "ecstasy", "delight", "wonder", "amazement",
    "awe", "admiration", "inspiration", "creativity", "imagination",
    "innovation", "ingenuity", "resourcefulness", "resilience",
    "strength", "courage", "bravery", "confidence", "optimism",
    "positivity", "hopefulness", "faith", "trust", "belief",
    "determination", "persistence", "patience", "endurance",
    "stamina", "vitality", "energy", "zeal", "enthusiasm",
    "passion", "drive", "motivation", "ambition", "goals",
    "dreams", "aspirations", "vision", "purpose", "meaning",
    "significance", "contribution", "impact", "influence",
    "leadership", "guidance", "support", "assistance", "cooperation",
    "collaboration", "unity", "harmony", "connection", "friendship",
    "companionship", "bonding", "togetherness", "solidarity", "teamwork",
    "synergy", "partnership", "fellowship", "celebration", "festivity",
    "rejoicing", "jubilation", "revelry", "cheerfulness", "lightheartedness",
    "positivity", "radiance"};
const char *negative_words[] = {"bad", "sad", "terrible", "horrible", "awful",
    "loss", "decline", "bearish", "downturn", "volatility",
    "risky", "downswing", "slump", "correction", "crash",
    "depreciation", "uncertainty", "turbulence", "bleak", "troubled",
    "struggling", "underperforming", "weak", "selloff", "unstable",
    "fluctuation", "downward trend", "bear market", "red", "negative sentiment",
    "pessimism", "fear", "panic", "uncertain outlook", "disappointment",
    "setback", "unfavorable", "unpromising", "bearish sentiment", "stagnant",
    "languishing", "deflation", "recession", "downgrade", "downside",
    "default", "default risk", "debt", "bankruptcy", "insolvency",
    "distress", "loss-making", "underperformance", "oversold", "undervalued"};

int count_sentiment(const char *text, const char *positive_words[], const char *negative_words[], int pos_size, int neg_size) {
    int count = 0;
    char word[1000000];
    bool negate_sentiment = false;

    char *token = strtok((char *)text, " "); // Remove const qualifier
    while (token != NULL) {
        strcpy(word, token);

        for (int i = 0; word[i] != '\0'; i++) {
            word[i] = tolower(word[i]);
        }

        if (strcmp(word, "not") == 0) {
            negate_sentiment = true;
        } else {
            for (int i = 0; i < pos_size; i++) { // Use passed size
                if (strcmp(word, positive_words[i]) == 0) {
                    count += negate_sentiment ? -1 : 1;
                    negate_sentiment = false;
                    break;
                }
            }
            for (int i = 0; i < neg_size; i++) { // Use passed size
                if (strcmp(word, negative_words[i]) == 0) {
                    count += negate_sentiment ? 1 : -1;
                    negate_sentiment = false;
                    break;
                }
            }
        }

        token = strtok(NULL, " ");
    }

    return count;
}

int main() {
    char text[100];

    printf("Enter a sentence: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    int positive_count = count_sentiment(text, positive_words, negative_words, sizeof(positive_words) / sizeof(positive_words[0]), sizeof(negative_words) / sizeof(negative_words[0]));
    int negative_count = count_sentiment(text, negative_words, positive_words, sizeof(negative_words) / sizeof(negative_words[0]), sizeof(positive_words) / sizeof(positive_words[0]));

    if (positive_count > negative_count) {
        printf("The sentence seems positive.\n");
    } else if (negative_count > positive_count) {
        printf("The sentence seems negative.\n");
    } else {
        printf("The sentence seems neutral.\n");
    }

    return 0;
}
