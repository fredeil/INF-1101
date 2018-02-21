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
	if (f == NULL) {
		perror("fopen");
		fatal_error("fopen() failed");
	}
	tokenize_file(f, wordlist);
	
	it = list_createiter(wordlist);
	while (list_hasnext(it)) {
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

	char *spamdir, *nonspamdir, *maildir;
	
	spamdir = argv[1];
	nonspamdir = argv[2];
	maildir = argv[3];

	list_t *spam_files = find_files(spamdir);
	list_t *non_spam_files = find_files(nonspamdir);
	list_t *mail_files = find_files(maildir);

    list_iter_t *iter = list_createiter(mail_files);
	while(list_hasnext(iter))
	{
		puts((char*)list_next(iter));
	}

	if (argc != 4) 
	{
		fprintf(stderr, "usage: %s <spamdir> <nonspamdir> <maildir>\n", argv[0]);
		return 1;
	}

    return 0;
}
