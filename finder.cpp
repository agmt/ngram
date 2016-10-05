#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <ios>
#include <random>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <algorithm>

#define TRY(x)                                                          \
    do {                                                                  \
    ssize_t __rc = (ssize_t)(x);                                                     \
    if( __rc < 0 ) {                                                  \
    fprintf(stderr, "ERROR: TRY(%s) failed\n", #x);                 \
    fprintf(stderr, "ERROR: at %s:%d\n", __FILE__, __LINE__);       \
    fprintf(stderr, "ERROR: rc=%d errno=%d (%s)\n",                 \
    (int)__rc, errno, strerror(errno));                          \
    exit(1);                                                        \
    }                                                                 \
    } while( 0 )

size_t ngrams_size;
char *ngrams;
char rdbuf[1024];

uint64_t left, right, mid;
struct timespec ts1, ts2;

static inline int64_t time_delta(const struct timespec &t1, const struct timespec &t2)
{
    return ((int64_t)(t2.tv_sec - t1.tv_sec))*1000000000LL + t2.tv_nsec-t1.tv_nsec;
}

static inline unsigned long time_delta(const unsigned long t1, const unsigned long t2)
{
    return ((t2-t1));
}

uint64_t getLineBegin(uint64_t p)
{
    for(;;)
    {
        if(p == 0)
            return p;
        if(ngrams[p] == '\n')
            return p + 1;
        p--;
    }
}

int main()
{
    int fd = open("gensorted3grams.txt", O_RDONLY|O_LARGEFILE);
    TRY(fd);
    ngrams_size = lseek(fd, 0, SEEK_END);
    ngrams = (char*)mmap(0, ngrams_size, PROT_READ, MAP_SHARED, fd, 0);
    TRY(ngrams);
    TRY(madvise(ngrams, ngrams_size, MADV_RANDOM));
    
    for(;;)
    {
        printf("Input your words: ");
        fgets(rdbuf, sizeof(rdbuf), stdin);
        if((rdbuf[0] == 0) || (rdbuf[0] == '\n'))
            break;
        rdbuf[strlen(rdbuf)-1] = 0;
        left = 0;
        right = ngrams_size-1;
        size_t rdbuf_len = strlen(rdbuf);
        clock_gettime(CLOCK_MONOTONIC, &ts1);
        for(;;)
        {
            if(left == right)
                break;
            mid = getLineBegin((left+right)/2);
            int res = memcmp(&ngrams[mid], rdbuf, rdbuf_len);
            if(res == 0)
                break;
            if(res > 0)
                right = mid;
            if(res < 0)
                left = mid;
        }
        clock_gettime(CLOCK_MONOTONIC, &ts2);
        printf("Found time=%ld off=%lu  line=%40.40s\n", time_delta(ts1, ts2), mid, &ngrams[mid]);
        
    }
    printf("See u\n");
    TRY(munmap(ngrams, ngrams_size));
    TRY(close(fd));
    return 0;
}
