#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <pthread.h>

struct file_tags
{
	char *title;
	char *artist;
	char *album;
	int track;
	int time;
	int filled;
};

struct plist_item
{
	char *file;
	char *title;
	struct file_tags *tags;
	short deleted;
};

struct plist
{
	int num;		/* Number of elements on the list */
	int allocated;		/* Number of allocated elements */
	pthread_mutex_t mutex;
	struct plist_item *items;
};

void plist_init (struct plist *plist);
int plist_add (struct plist *plist, const char *file_name);
void plist_add_from_item (struct plist *plist, const struct plist_item *item);
char *plist_get_file (struct plist *plist, int i);
int plist_next (struct plist *plist, int num);
void plist_clear (struct plist *plist);
void plist_delete (struct plist *plist, const int num);
void plist_free (struct plist *plist);
void plist_sort_fname (struct plist *plist);
int plist_find_fname (struct plist *plist, const char *file);
struct file_tags *tags_new ();
void tags_free (struct file_tags *tags);
char *build_title (const struct file_tags *tags);
int plist_rand (struct plist *plist);
int plist_count (struct plist *plist);
void plist_set_title (struct plist *plist, const int num, const char *title);
void plist_set_file (struct plist *plist, const int num, const char *file);
int plist_deleted (const struct plist *plist, const int num);

#endif
