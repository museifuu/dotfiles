# i3 config file (v4)
#
# Please see https://i3wm.org/docs/userguide.html for a complete reference!

# toggle split direction for each window
for_window [class="^"] split toggle
default_orientation vertical

set $mod Mod4

# Use Mouse+$mod to drag floating windows to their wanted position
floating_modifier $mod

# start a terminal
bindsym $mod+Return exec urxvt

# kill focused window
bindsym $mod+Shift+q kill; split toggle

# start rofi
bindsym $mod+d exec rofi -show run

# alternatively, you can use the cursor keys:
bindsym $mod+Left focus left
bindsym $mod+Down focus down
bindsym $mod+Up focus up
bindsym $mod+Right focus right

# alternatively, you can use the cursor keys:
bindsym $mod+Shift+Left move left
bindsym $mod+Shift+Down move down
bindsym $mod+Shift+Up move up
bindsym $mod+Shift+Right move right

# enter fullscreen mode for the focused container
bindsym $mod+f fullscreen toggle

# change container layout (stacked, tabbed, toggle split)
bindsym $mod+s layout stacking
bindsym $mod+w layout tabbed
bindsym $mod+e layout toggle split

# toggle tiling / floating
bindsym $mod+space floating toggle

### Workspaces

  # Define names for default workspaces for which we configure key bindings later on.
  # We use variables to avoid repeating the names in multiple places.
  set $ws1 "1"
  set $ws2 "2"
  set $ws3 "3"
  set $ws4 "4"
  set $ws5 "5"
  set $ws6 "6"
  set $ws7 "7"
  set $ws8 "8"
  set $ws9 "9"
  set $ws10 "10"

  # switch to workspace
  bindsym $mod+1 workspace $ws1
  bindsym $mod+2 workspace $ws2
  bindsym $mod+3 workspace $ws3
  bindsym $mod+4 workspace $ws4
  bindsym $mod+5 workspace $ws5
  bindsym $mod+6 workspace $ws6
  bindsym $mod+7 workspace $ws7
  bindsym $mod+8 workspace $ws8
  bindsym $mod+9 workspace $ws9
  bindsym $mod+0 workspace $ws10

  # move focused container to workspace
  bindsym $mod+Shift+1 move container to workspace $ws1
  bindsym $mod+Shift+2 move container to workspace $ws2
  bindsym $mod+Shift+3 move container to workspace $ws3
  bindsym $mod+Shift+4 move container to workspace $ws4
  bindsym $mod+Shift+5 move container to workspace $ws5
  bindsym $mod+Shift+6 move container to workspace $ws6
  bindsym $mod+Shift+7 move container to workspace $ws7
  bindsym $mod+Shift+8 move container to workspace $ws8
  bindsym $mod+Shift+9 move container to workspace $ws9
  bindsym $mod+Shift+0 move container to workspace $ws10

# reload the configuration file
bindsym $mod+Shift+c reload
# restart i3 inplace (preserves your layout/session, can be used to upgrade i3)
bindsym $mod+Shift+r restart
# exit i3 (logs you out of your X session)
bindsym $mod+Shift+e exec "i3-nagbar -t warning -m 'You pressed the exit shortcut. Do you really want to exit i3? This will end your X session.' -B 'Yes, exit i3' 'i3-msg exit'"

# resize window (you can also use the mouse for that)
mode "resize" {
        # These bindings trigger as soon as you enter the resize mode

        # Pressing left will shrink the window’s width.
        # Pressing right will grow the window’s width.
        # Pressing up will shrink the window’s height.
        # Pressing down will grow the window’s height.
        bindsym Left resize shrink width 10 px or 10 ppt
        bindsym Down resize grow height 10 px or 10 ppt
        bindsym Up resize shrink height 10 px or 10 ppt
        bindsym Right resize grow width 10 px or 10 ppt

        # back to normal: Enter or Escape or $mod+r
        bindsym Return mode "default"
        bindsym Escape mode "default"
        bindsym $mod+r mode "default"
}

bindsym $mod+r mode "resize"

### Startup options

# Disable window titlebars entirely
for_window [class="^.*"] border pixel 2

# Smart borders (draw borders around container only if it is not the only container on this workspace)
# on|no_gaps (on=always activate and no_gaps=only activate if the gap size to the edge of the screen is 0)
smart_borders on

exec --no-startup-id polybar -r bar
exec --no-startup-id feh --bg-scale /home/user/Images/background.png
#exec --no-startup-id xcompmgr -cCfn -I0.06 -O0.07
exec --no-startup-id compton --config /home/user/.config/compton.conf
exec --no-startup-id steam-native -silent
