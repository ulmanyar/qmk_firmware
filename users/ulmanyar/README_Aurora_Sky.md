# `keymap.c`:

```c
#include "aurora_sky.h"
```

And in `process_record_user(...)`:

```c
#ifdef AURORA_SKY
if (record->event.pressed) {
    set_aurora_typing_state(true);
}
#endif
```
And something like:

```c
#ifdef AURORA_SKY
bool oled_task_user(void) {
    render_aurora_sky();
    return false;
}
#endif
```


# `rules.mk`
```
SRC += aurora_sky.c
```

# `config.h`
```
#define AURORA_SKY
```