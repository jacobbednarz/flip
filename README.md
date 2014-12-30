# Flip

Flip is a module designed to make feature flipping straight forward in Drupal.

### Installation  

Clone the repository into your modules directory.

```
git clone git@github.com:jacobbednarz/flip.git
```

### Usage

In order to use a feature toggle, you must first register with flip by implementing `hook_flip_info`.

```php
function MYMODULE_flip_info() {
  return array(
    'example_toggle' => array(
      'name' => 'Example toggle',
      'description' => 'This is my example description for a toggle.',
      'condition' => 'my_condition_check',
    ),
  );
}
```

 Within this info hook, the following keys are available:

- `name`: The friendly name of the toggle. This is displayed in the UI.
- `description`: The overview of your toggle. I.e. what is it's purpose?
- `condition`: The callback to evaluate and determine if your toggle should be
  fired off.

### Enabling a feature toggle

Once you have defined the `hook_flip_info`, flush caches and all the
implementing toggles should now be visible at `admin/config/development/flip`.

Note: For a toggle to work, it must be marked as enabled in
`admin/config/development/flip` **AND** the condition callback must return
`TRUE`.

To apply it conditionally within your code, you may have something similar to the following:

```php
// Account for both outcomes. Handy for backwards compatibility.
if (flip_enabled('example_toggle')) {
  do_awesome_new_thing();
}
else {
  use_old_functionality();
}

// Just do something new.
if (flip_enabled('example_toggle')) {
  do_awesome_new_thing();
}
```

### Example callbacks

- Only during business hours

```php
function flip_business_hours() {
  if (date('H') > 8 && date('H') < 16) {
    return TRUE;
  }

  return FALSE;
}
```
