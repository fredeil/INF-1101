/* Author: Steffen Viken Valvaag <steffenv@cs.uit.no> */
#include "list.h"
#include "set.h"
#include "common.h"

/*
 * Case-insensitive comparison function for strings.
 */
static int compare_words(void *a, void *b)
{
    return strcasecmp(a, b);
}

/*
 * Returns the set of (unique) words found in the given file.
 */
static set_t *tokenize(char *filename)
{
	set_t *wordset = set_create(compare_words);
	list_t *wordlist = list_create(compare_words);
	list_iter_t *it;
	FILE *f;
	
	f = fopen(filename, "r");
	if (f == NULL) 
	{
		perror("fopen");
		fatal_error("fopen() failed");
	}

	tokenize_file(f, wordlist);
	
	it = list_createiter(wordlist);
	while (list_hasnext(it)) 
	{
		set_add(wordset, list_next(it));		
	}

	list_destroyiter(it);
	list_destroy(wordlist);
	return wordset;
}

/*
 * Prints a set of words.
 */
static void printwords(char *prefix, set_t *words)
{
	set_iter_t *it;
	
	it = set_createiter(words);
	printf("%s: ", prefix);
	while (set_hasnext(it)) {
		printf(" %s", set_next(it));
	}
	printf("\n");
	set_destroyiter(it);
}

/*
 * Main entry point.
 */
int main(int argc, char **argv)
{
	int numdir = argc - 1;
	set_t *mail_words[5], *spam_words[4], *non_spam_words[4];

	if (argc != 4) 
	{
		fprintf(stderr, "usage: %s <spamdir> <nonspamdir> <maildir>\n", argv[0]);
		return 1;
	}

	list_t *files[numdir];
	list_iter_t *file_iter;

	// Get all words from all spam, non-spam and mail
	for(int i = 0; i < numdir; i++)
	{
		files[i] = find_files(argv[i + 1]);
		file_iter = list_createiter(files[i]);

		int j = 0;
		while(list_hasnext(file_iter))
		{
			char *file = list_next(file_iter);
			switch(i)
			{
				case 0: spam_words[j] = tokenize(file); break;
				case 1: non_spam_words[j] = tokenize(file); break;
				case 2: mail_words[j] = tokenize(file); break;
			}
			j++;
		}
		list_destroyiter(file_iter);
	}


	set_t *difference;
	set_t *nonspam_union;
	set_t *spam_intersection;

	// Non spam union
	set_t *ab = set_union(non_spam_words[0], non_spam_words[1]);
	set_t *cd = set_union(non_spam_words[2], non_spam_words[3]);
	nonspam_union = set_union(ab, cd);
	set_destroy(ab);
	set_destroy(cd);

	// Spam intersection
	ab = set_intersection(spam_words[0], spam_words[1]);
	cd = set_intersection(spam_words[2], spam_words[3]);
    spam_intersection = set_intersection(ab, cd);
	set_destroy(ab);
	set_destroy(cd);

	// Subtract spam and non spam
	difference = set_difference(spam_intersection, nonspam_union);

	list_iter_t *iter = list_createiter(files[2]);

    for(int i = 0; i < 5; i ++)
	{
		set_t *set = set_intersection(mail_words[i], difference);
		int count = set_size(set);
		char* str = count == 0 ? "Non spam" : "SPAM";
		printf("%s: %d spam word(s) -> %s\n", (char*)list_next(iter), count, str);
		set_destroy(set);
	}

	// Clean up files
	for(int i = 0; i < numdir; i++)
	{
		list_destroy(files[i]);
	}

	for(int i = 0; i < 4; i++)
	{
		set_destroy(spam_words[i]);
		set_destroy(non_spam_words[i]);
	}

	list_destroyiter(iter);
	set_destroy(difference);
	set_destroy(nonspam_union);
	set_destroy(spam_intersection);
    return 0;
}
