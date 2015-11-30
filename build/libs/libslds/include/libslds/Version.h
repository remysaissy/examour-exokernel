#ifndef slds_VERSION_H
#define slds_VERSION_H

 /* The current major version. */
#define slds_VERSION_MAJOR 0

/* The current minor version. */
#define slds_VERSION_MINOR 0

/* The current patch level. */
#define slds_VERSION_PATCH 0

/* The current git revision. */
#define slds_VCS_REVISION "7072124a6d8543c698aa344c8d615444c0d7b5a6"

 /* True if the current version is newer than the given one. */
#define HELLO_VERSION_GT(MAJOR, MINOR, PATCH) \
  ((slds_VERSION_MAJOR > MAJOR) ||           \
   (slds_VERSION_MAJOR ==                    \
    MAJOR&&(slds_VERSION_MINOR > MINOR || (slds_VERSION_MINOR == MINOR&& slds_VERSION_PATCH > PATCH))))

/* True if the current version is equal or newer to the given. */
#define slds_VERSION_GE(MAJOR, MINOR, PATCH) \
  ((slds_VERSION_MAJOR > MAJOR) ||           \
   (slds_VERSION_MAJOR ==                    \
    MAJOR&&(slds_VERSION_MINOR > MINOR || (slds_VERSION_MINOR == MINOR&& slds_VERSION_PATCH >= PATCH))))

/* True if the current version is older than the given one. */
#define slds_VERSION_LT(MAJOR, MINOR, PATCH) \
  ((slds_VERSION_MAJOR < MAJOR) ||           \
   (slds_VERSION_MAJOR ==                    \
    MAJOR&&(slds_VERSION_MINOR < MINOR || (slds_VERSION_MINOR == MINOR&& slds_VERSION_PATCH < PATCH))))

/* True if the current version is older or equal to the given. */
#define slds_VERSION_LE(MAJOR, MINOR, PATCH) \
  ((slds_VERSION_MAJOR < MAJOR) ||           \
   (slds_VERSION_MAJOR ==                    \
    MAJOR&&(slds_VERSION_MINOR < MINOR || (slds_VERSION_MINOR == MINOR&& slds_VERSION_PATCH <= PATCH))))


/* Get the version string. */
#define slds_VERSION \
  slds_VERSION_MAJOR ## "." ## slds_VERSION_MINOR ## "." ## slds_VERSION_PATCH

#endif /* slds_VERSION_H */

