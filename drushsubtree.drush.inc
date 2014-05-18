<?php

/**
 * @file
 * drushsubtree drush command.
 *
 *  You can copy this file to any of the following
 *    1. A .drush folder in your HOME folder.
 *    2. Anywhere in a folder tree below an active module on your site.
 *    3. /usr/share/drush/commands (configurable)
 *    4. In an arbitrary folder specified with the --include option.
 *    5. Drupal's /drush or /sites/all/drush folders.
 */

require_once 'drushsubtree.subtreecommander.class.inc';
require_once 'drushsubtree.gitcommander.class.inc';

/**
 * Implements hook_drush_command().
 */
function drushsubtree_drush_command() {
  $items = array();
  $standard_command_options = _drushsubtree_standard_command_options();

  $items['subtree'] = array(
    'description' => 'An interface for running drushsubtree commands with more git-like syntax. (All options for all commands are supported. See `drush subtree-<command>` --help for documentation about options for particular commands.)',
    'arguments' => array(
      'command' => '',
      'project' => '',
    ),
    'options' => $standard_command_options,
    'examples' => array(
      'drush subtree' => 'When args and options are missing, displays usage instructions.',
      'drush subtree <command> <project>' => '',
      'drush subtree add <project>' => '',
      'drush subtree pull <project>' => '',
      'drush subtree push <project>' => '',
      'drush subtree merge <project> <id>' => '',
      'drush subtree checkout <project> <tag>' => '',
    ),
    // No bootstrap at all.
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'drush dependencies' => 'buildmanager',
  );

  $items['subtree-add'] = array(
    'description' => '',
    'arguments' => array(
      'project' => '(Optional) Subtree defined in buildmanager config.',
    ),
    'options' => $standard_command_options,
    'examples' => array(
      'drush subtree-add' => '',
    ),
    // No bootstrap at all.
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'drush dependencies' => 'buildmanager',
  );

  $items['subtree-pull'] = array(
    'description' => '',
    'arguments' => array(
      'project' => '(Optional) Subtree defined in buildmanager config.',
    ),
    'options' => $standard_command_options,
    'examples' => array(
      'drush subtree-pull' => '',
    ),
    // No bootstrap at all.
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'drush dependencies' => 'buildmanager',
  );

  $items['subtree-merge'] = array(
    'description' => '',
    'arguments' => array(
      'project' => '(Optional) Specify a subtree defined in buildmanager config.',
      'commit ID' => '(Optional) Override ID/tag specified in make file(s).',
    ),
    'options' => $standard_command_options,
    'examples' => array(
      'drush subtree-merge' => '',
      'drush subtree-merge <my project>' => '',
      'drush subtree-merge <my project> <commit id>' => '',
    ),
    // No bootstrap at all.
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'drush dependencies' => 'buildmanager',
  );

  $push_options = $standard_command_options;
  unset($push_options['message']);
  $items['subtree-push'] = array(
    'description' => '',
    'arguments' => array(
      'project' => '',
    ),
    'options' => $push_options,
    'examples' => array(
      'drush subtree-push' => '',
    ),
    // No bootstrap at all.
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'drush dependencies' => 'buildmanager',
  );

  $items['subtree-checkout'] = array(
    'description' => 'Faux subtree command. "Checkout" a tagged version of a subtree project.',
    'arguments' => array(
      'project' => '',
      'tag or commit ID' => 'Git tag or commit ID. (Check available tags with drushsubtree-get-tags. Commit IDs must be passed as full 40 character SHA1 hash. 40 character tags are not supported.)',
    ),
    'options' => $standard_command_options,
    'examples' => array(
      'drush subtree-checkout <project> <id>' => '',
      'drush subtree-checkout <project> <tag>' => '',
    ),
    // No bootstrap at all.
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'drush dependencies' => 'buildmanager',
  );

  $items['subtree-get-tags'] = array(
    'description' => "View tagged releases for a subtree project.",
    'arguments' => array(
      'project_name' => '',
    ),
    'examples' => array(
      'drush subtree-get-tags <my-project>' => '',
      'drush subtree-ls-tags <my-project>' => '',
    ),
    'aliases' => array('subtree-ls-tags'),
    // No bootstrap at all.
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'drush dependencies' => 'buildmanager',
  );

  $items['subtree-get-head'] = array(
    'description' => "Get HEAD commit id for subtree project (display corresponding tag, if there is one.",
    'arguments' => array(
      'project_name' => '',
    ),
    'examples' => array(
      'drush subtree-get-head <my-project>' => '',
      'drush subtree-split <my-project>' => 'Same as `git subtree split --prefix=<my-project>`',
    ),
    'aliases' => array('subtree-split'),
    // No bootstrap at all.
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'drush dependencies' => 'buildmanager',
  );

  $items['subtree-get-head-remote'] = array(
    'description' => "Get HEAD commit id for subtree project's remote repo.",
    'arguments' => array(
      'project_name' => '',
    ),
    'examples' => array(
      'drush subtree-get-remote-head <my-project>' => '',
    ),
    'aliases' => array('subtree-get-remote-head'),
    // No bootstrap at all.
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'drush dependencies' => 'buildmanager',
  );

  $items['subtree-get-subtrees'] = array(
    'description' => "View a list of subtree projects specified in buildmanager config",
    'examples' => array(
      'drush subtree-show-subtrees' => '',
      'drush sss' => '',
    ),
    'aliases' => array('sss'),
    // No bootstrap at all.
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'drush dependencies' => 'buildmanager',
  );

  $items['subtree-get-info'] = array(
    'description' => "Get info from config file for subtree.",
    'examples' => array(
      'drush subtree-get-info' => '',
      'drush sgi' => '',
    ),
    'aliases' => array('sgi'),
    // No bootstrap at all.
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'drush dependencies' => 'buildmanager',
  );

  $items['subtree-compare-heads'] = array(
    'description' => "Compare local subtree HEAD with remote HEAD.",
    'arguments' => array(
      'project_name' => '',
    ),
    'examples' => array(
      'drush subtree-compare-heads' => 'Use prompt to select project',
      'drush subtree-compare-heads <my-project>' => '',
      'drush sch <my-project>' => '',
    ),
    'aliases' => array('sch'),
    // No bootstrap at all.
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'drush dependencies' => 'buildmanager',
  );

  $items['subtree-compare-tag'] = array(
    'description' => "Compare local subtree HEAD with tag in make file.",
    'arguments' => array(
      'project_name' => '',
    ),
    'examples' => array(
      'drush subtree-compare-tags' => 'Use prompt to select project',
      'drush subtree-compare-tags <my-project>' => '',
      'drush sct <my-project>' => '',
    ),
    'aliases' => array('sct'),
    // No bootstrap at all.
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'drush dependencies' => 'buildmanager',
  );

  return $items;
}

/**
 * Returns array of standard subtree options, used for multiple commands.
 *
 * @return array
 *   Options to be used in any command following pattern drush subtree <command>
 */
function _drushsubtree_standard_command_options() {
  return array(
    'config_file' => array(
      'description' => 'path/to/buildmaster.config.yml',
    ),
    'message' => array(
      'description' => 'Message to include at the beginning of new commits. (Note: subtree add, merge, pull all generate commits in your parent repo.)',
    ),
    'simulate' => array(
      'description' => 'Output commands to be executed for examination, but do not actually execute them.',
    ),
  );
}

/**
 * Callback for drushsubtree-get-tags().
 */
function drush_drushsubtree_subtree_get_tags($subtree_name) {
  // Get config.
  $config = _drushsubtree_get_config();
  if (!$details = $config['subtrees'][$subtree_name]) {
    return drush_set_error(dt('No subtree config available for !subtree in !config_file'),
      array('!subtree' => $subtree_name, '!config_file' => $config_file));
  }

  // Look up tags from remote specified in $details.
  $tags = drushsubtree_list_remote_tags($subtree_name, $details);

  foreach ($tags as $tag => $id) {
    drush_print("{$tag}\t{$id}");
  }
}

/**
 * Callback for drushsubtree-get-head().
 */
function drush_drushsubtree_subtree_get_head($subtree_name) {
  // Get config.
  $config = _drushsubtree_get_config();
  if (!$details = $config['subtrees'][$subtree_name]) {
    return drush_set_error(dt('No subtree config available for !subtree in !config_file'),
      array('!subtree' => $subtree_name, '!config_file' => $config_file));
  }

  $head = drushsubtree_subtree_get_head($subtree_name, $details);
  $result = "{$subtree_name}\tHEAD\t{$head}";

  // Check for matching tag.
  if ($tag = _drushsubtree_match_tag($subtree_name, $head, $details)) {
    $result .= "\t{$tag}";
  }

  // Print result.
  drush_print($result);
}

/**
 * Get HEAD for local subtree project.
 *
 * @param string $subtree_name
 *   Project name.
 *
 * @param array $details
 *   Project details from buildmanager config.
 *
 * @return string
 *   Commit ID for HEAD
 */
function drushsubtree_subtree_get_head($subtree_name, $details) {
  // Instantiated subtree command generator.
  $subtree = new SubtreeCommander($subtree_name, $details);

  // Execute split command to get commit id.
  exec($subtree->split(), $output, $exit_code);
  if ($exit_code !== 0) {
    drush_log(drush_print_r($output), 'error');
    return drush_set_error(dt("Sorry. Git subtree split failed. Couldn't retrieve HEAD."));
  }
  // Retrieve HEAD.
  $head = $output[0];

  return $head;
}

/**
 * Callback for drushsubtree-get-remote-head().
 */
function drush_drushsubtree_subtree_get_remote_head($subtree_name) {
  // Get config.
  $config = _drushsubtree_get_config();
  if (!$details = $config['subtrees'][$subtree_name]) {
    return drush_set_error(dt('No subtree config available for !subtree in !config_file'),
      array('!subtree' => $subtree_name, '!config_file' => $config_file));
  }

  // Get HEAD.
  $uri = $details['uri'];
  $branch = $details['branch'];
  $head = drushsubtree_get_remote_head($uri, $branch);

  // Print result.
  drush_print("{$head}\t{$uri}\t{$branch}");
}

/**
 * Get HEAD for branch on some remote repo.
 *
 * @param string $uri
 *   URI for remote repo.
 *
 * @param string $branch
 *   Branch on remote repo
 *
 * @return string
 *   Commit ID for remote HEAD
 */
function drushsubtree_get_remote_head($uri, $branch) {
  // Instantiated git command generator.
  $git = new GitCommander(array('uri' => $uri, 'branch' => $branch));

  // Get remote HEAD. The command will look like this:
  // git ls-remote --heads https://github.com/whitehouse/petitions 7.x-2.x
  $command = $git->getRemoteHead();
  exec($command, $output, $exit_code);

  // Handle failure.
  if ($exit_code !== 0) {
    return drush_set_error('drushsubtree', dt("Request for remote head list failed: !command", array('!command' => $command)));
  }

  // Parse result. The output will look like this:
  // 065f1f81709febfcb0d1429b100a1709d64c1c4d  refs/heads/7.x-2.x
  $parts = explode("\t", $output[0]);
  $head = $parts[0];

  return $head;
}

/**
 * Find tag corresponding to commit ID (if one exists).
 *
 * @param string $name
 *   Subtree project name.
 *
 * @param string $id
 *   Git commit ID.
 *
 * @param array $details
 *   Subtree project details from buildmanager config file.
 *
 * @return string|bool
 *   Tag name, false if not available.
 */
function _drushsubtree_match_tag($name, $id, $details) {
  // Assume there's no match unless we find one.
  $matching_tag = FALSE;

  // Check remote tags for matching commit ID.
  foreach (drushsubtree_list_remote_tags($name, $details) as $tag => $tag_id) {
    if ($id == $tag_id) {
      $matching_tag = $tag;
    }
  }

  return $matching_tag;
}


/**
 * Get message to be included with subtree add/pull/merge commits.
 *
 * Site make config files can specify a message to be included
 * project-by-project.
 *
 * @param string $subtree_message
 *   Defined in buildmanager YAML config file.
 *
 * @return string
 *   A commit message flag to a git subtree add, pull, or merge command.
 *   Empty string if no message should be added.
 */
function _drushsubtree_add_subtree_commit_message($subtree_message = '') {
  $drush_message = drush_get_option('message', '');
  if ($drush_message || $subtree_message) {
    $custom_message = ($drush_message) ? "{$drush_message}\n\n\t{$subtree_message}" : $subtree_message;
  }
  $message = ($custom_message) ? " --message='{$custom_message}'" : '';

  return $message;
}

/**
 * Get prefix (path) to local subtree.
 *
 * @param string $directory
 *   Name of directory where subtree should go.
 *
 * @return string
 *   Path to subtree from top-level of repo to be used for --prefix.
 */
function _drushsubtree_get_prefix($directory) {
  return "projects/{$directory}";
}

/**
 * Get URI for remote git repo.
 *
 * @param array $details
 *   Relevant details for git subtree add command.
 *
 * @return string|bool
 *   Uri for git repo.
 */
function _drushsubtree_get_uri($details) {
  if (!(isset($details['uri']) || !strlen($details['uri']) > 0)) {
    return drush_set_error('drushsubtree', dt("uri is a required subtree parameter for any subtree included here. Please add this to your site's config file, then try again."), 'error');
  }
  else {
    return $details['uri'];
  }
}

/**
 * Get subtree branch from drushsubtree project details included in config file.
 *
 * @param array $details
 *   Relevant details for git subtree add command:
 *
 * @return string|bool
 *   Branch name.
 */
function _drushsubtree_get_branch($details) {
  if (!(isset($details['branch']) || !strlen($details['branch']) > 0)) {
    return drush_set_error('drushsubtree', dt("branchis a required subtree parameter for any subtree included here. Please add this to your site's config file, then try again."), 'error');
  }

  return $details['branch'];
}

/**
 * Figure out what version of a subtree project should be checked out.
 *
 * Return commit ID so "checkout" can be done as a subtree merge.
 *
 * @param string $subtree_name
 *   Name of subtree.
 *
 * @param array $project_info
 *   Info about a project from parsed make files.
 *
 * @param array $details
 *   Details about subtree project from buildmanager config.
 *
 * @param string $tag
 *   Tag, if available. Empty if not.
 *
 * @return string
 *   Commit ID for subtree to be merged to. Empty if unavailable.
 */
function _drushsubtree_get_project_id($subtree_name, $project_info, $details, $tag = '') {
  $id = '';

  // First, try getting ID ("revision") from make files.
  $id = _drushsubtree_get_id_from_make_info($subtree_name, $project_info);

  // If no commit ID was specified in make file(s), try looking up ID using
  // remote list of tags.
  if (!$id) {
    // Get an array of commit IDs keyed by tags.
    $tags = drushsubtree_list_remote_tags($subtree_name, $details);
    if (!$tags) {
      // Attempt to retrieved tags from remote failed.
      drush_log(dt("Commit IDs for !name tags could not be retrieved from !remote.\nTo explicitly designate which commit ID to check out, you can add this to your makefile (replace abc1234 with a real commit ID):\n\tprojects[!name][download][revision] = abc1234",
        array('!name' => $subtree_name, '!remote' => $details['uri'])), 'warning');
    }
  }
  elseif ($tags && !$tag) {
    // Tags were retrieved successfully. No tag was passed in. See if we can get
    // tag/version from make file(s).
    $config = _drushsubtree_get_config();
    $core = buildmanager_get_core_version($config);
    $tag = _drushsubtree_get_project_tag($subtree_name, $project_info, $core);
  }

  // If we've got an array of IDs keyed by tags ($tags) and a tag to look up
  // ($tags), we've got what we need now.
  if ($tags && $tag) {

    // Error handling. Make sure the tag specified in the make file(s) is
    // available in the remote we're pulling commit IDs from.
    if (!isset($tags[$tag])) {
      $message = dt("The version/tag specified by your build.make file does not correspond with tags available at the remote we're pulling from.");
      $message .= "\n" . dt("Review available tags like this: !command",
        array('!command' => "\n\tdrush subtree-get-tags {$subtree_name}"));
      // Display specs determined by make file and buildmanager config for user
      // to review.
      $specs = '';
      $specs .= "\n\tproject:\t{$subtree_name}";
      $specs .= "\n\ttag:\t\t{$tag}";
      $specs .= "\n\tremote:\t\t{$details['uri']}";
      $message .= "\n" . dt("Or see if you can spot a mistake in your make file or buildmanager config here: !specs",
        array('!specs' => $specs));
      return drush_set_error($message);
    }

    // Check for annotated tags. Use those when available. Otherwise users end
    // up getting a confusing 'fatal: bad object' error message from git.
    // Annotated tags look like this: 7.x-2.0^{} for 7.x-2.0.
    $annotated_tag = "{$tag}^{}";
    if (isset($tags[$annotated_tag])) {
      $tag = $annotated_tag;
    }

    // Success!
    $id = $tags[$tag];
  }

  return $id;
}

/**
 * Get a commit ID ("revision") from a drush make file info.
 *
 * @param string $project_name
 *   Name of project (module, profile, theme, library).
 *
 * @param array $project_info
 *   Project info array from make files.
 *
 * @return string|bool
 *   Project revision (commit) id specified in make file. False if unavailable.
 */
function _drushsubtree_get_id_from_make_info($project_name, $project_info) {
  $id = (isset($project_info['download']['revision'])) ? $project_info['download']['revision'] : FALSE;
  return $id;
}

/**
 * Retrieve list of tags and corresponding commit IDs from remote repository.
 *
 * @param string $project_name
 *   Name of project (module, profile, theme, library).
 *
 * @param array $details
 *   From drushsubtree config.
 *
 * @return array|bool
 *   Commit IDs keyed by tag name. False for failure.
 */
function drushsubtree_list_remote_tags($project_name, $details) {
  // Instantiate git command generator.
  $git = new GitCommander(array('uri' => $details['uri']));

  // Get a list of commit IDs and corresponding tags. A successful request
  // returns something like this:
  // 516726690a5f3a15ccf8d7ffccd135db4375ad10  refs/tags/7.x-1.0-rc1
  // e214ea5b94f345b66f302d0d4aae232b4128c1e3  refs/tags/7.x-1.0-rc2
  // 8f61c66e5f55e72a35f4a1b8f4eee93a428a03ac  refs/tags/7.x-1.0-rc3
  $command = $git->listRemoteTags();

  // Each line of output is stored in $output array.
  // $exit_code is 0 for success, anything else for failure.
  exec($command, $output, $exit_code);

  // Handle failure.
  if ($exit_code !== 0) {
    return drush_set_error('drushsubtree', dt("Request for remote tag list failed: !command", array('!command' => $command)));
  }

  // Parse result.
  $tags = array();
  foreach ($output as $line) {
    // Example line: 8f61c66e5f55e72a35f4a1b8f4eee93a428a03ac  refs/tags/7.x-1.0
    $parts = explode("\t", $line);
    if (count($parts) < 2) {
      // Skip empty lines that sneak in.
      continue;
    }
    $pos = strlen('refs/tags/');
    $tag = substr($parts[1], $pos);
    $id = $parts[0];
    $tags[$tag] = $id;
  }

  return $tags;
}

/**
 * Get tag/version for a project specified in make file(s).
 *
 * @param string $project_name
 *   Name of project (module, profile, theme, library).
 *
 * @param array $project_info
 *   Project info array from make files.
 *
 * @param string $core
 *   Core version (e.g. 6.x, 7.x, 8.x). Required if tag is being looked up from
 *   a project's version number in a make file.
 *
 * @return string
 *   Project version number specified in make file. Empty if unavailable.
 */
function _drushsubtree_get_project_tag($project_name, $project_info, $core = '') {
  $tag = '';

  if (isset($project_info['version']) && $core) {
    $version = $project_info['version'];
    $tag = "{$core}-{$version}";
  }
  elseif (isset($project_info['tag'])) {
    $tag = $project_info['tag'];
  }
  elseif (isset($project_info['download']['tag'])) {
    $tag = $project_info['download']['tag'];
  }
  else {
    // Make files do not specify any tag for this project.
    drush_log(dt("No tag or commit ID available for !name.",
                  array('!name' => $project_name), 'warning'));
  }

  return $tag;
}

/**
 * Return command to generate symlink to subtree.
 *
 * This command must be run from top-level of repo.
 *
 * @param string $name
 *   Name of project (module, theme, profile) to be replaced with a symlink to a
 *   subtree inside /projects.
 *
 * @param string $path
 *   Path to project in Drupal code base, relative to top-level of site repo.
 *
 * @return string
 *   Shell command for adding symlink.
 */
function _drushsubtree_subtree_add_symlink($name, $path) {
  // Get path to subtree, relative to top-level directory.
  $prefix = _drushsubtree_get_prefix($name);

  // Get source, relative to parent directory inside docroot.
  $count = count(explode('/', $path));
  $source = '';
  for ($i = 0; $i < $count - 1; $i++) {
    $source .= '../';
  };
  // Add prefix to relative source path.
  $source .= $prefix;

  // Parent directory for symlink.
  $pos = strpos($path, $name);
  $parent_directory = substr($path, 0, $pos);

  // Remove the directory. Replace it with a symlink.
  $command = "rm -rf {$path}; cd {$parent_directory}; ln -s {$source} {$name};";

  return $command;
}

/**
 * Implements hook_buildmanager_build().
 *
 * Check for subtrees in config file. Add/update subtrees in build.
 *
 * param array $info
 *   Info from drush make build file.
 *
 * param array $config
 *   Configuration defined in buildmanager.config.yml
 *
 * param obj $commands
 *   Commands to be executed by buildmanager.
 *   - precommands (array), commands to execute before `drush make` (re)build
 *   - postcommands (array), commands to execute after `drush make` (re)build
 */
function drushsubtree_buildmanager_build($info, $config, $commands) {
  // Check for subtrees in $config.
  if (!isset($config['subtrees'])) {
    // This project has no subtrees. Our work here is done.
    return;
  }

  drush_log(dt('Preparing to add/update git subtrees.'), 'ok');

  // Prep projects directory. All subtrees will use --prefix=projects/$name
  _drushsubtree_prep_projects_directory();

  // Get subtree commands to be executed before running `drush make`.
  $subtree_commands = array();

  // Get symlink commands to be run after `drush make`.
  $symlink_commands = array();

  // Loop through all subtrees described in buildmanager config to add prebuild
  // and postbuild commands.
  // Prebuild:
  // - Validation checks and warnings.
  // - Subtree updates (add, pull, merge).
  // Postbuild:
  // - Symlinks (which will get blown away by drush make) are restored.
  foreach ($config['subtrees'] as $subtree_name => $details) {

    // Start with postbuild commands (adding symlinks) because prebuild commands
    // are sometimes skipped (when no-subtree-updates flag is set).
    // Remove files checked out by drush. Add symlink pointing to local subtree.
    drush_log(dt('Preparing to symlink !subtree_name to path: !path', array('!subtree_name' => $subtree_name, '!path' => $details['path'])), 'ok');
    $symlink_commands[] = _drushsubtree_subtree_add_symlink($subtree_name, $details['path']);

    // Next add prebuild commands / subtree repo updates.
    if (drush_get_option('no-subtree-updates', FALSE)) {
      // If no-subtree-updates flag is set, skip the rest of the foreach loop.
      drush_log(dt('Skipping git subtree updates.'), 'ok');
      continue;
    }

    // Get project info.
    $project_info = array();
    if (isset($info['projects'][$subtree_name])) {
      $project_info = $info['projects'][$subtree_name];
    }
    // If it's not a "project" it's a "library".
    elseif (isset($info['libraries'][$subtree_name])) {
      $project_info = $info['libraries'][$subtree_name];
    }
    // Can't find info in available make files.
    else {
      drush_log(dt("Could not find info in make file(s) about this project: !name",
        array('!name' => $subtree_name)), 'warning');
    }

    // Get tagged version of project from make file, if available.
    $tag = _drushsubtree_get_project_tag($subtree_name, $project_info, $info['core']);

    // Get git commit ID to merge, if enough info is available.
    $id = _drushsubtree_get_project_id($subtree_name, $project_info,
                                       $details, $tag);

    // Run subtree developer checks?
    if (drush_get_option('subtree-dev-checks', FALSE)) {
      $checks_pass = _drushsubtree_dev_checks($name, $tag, $id, $details);
      if (!$checks_pass) {
        // User canceled build.
        drush_log(dt('Drush Subtree: Canceling build.'), 'error');
        // Returning anything cancels the build.
        return 'Drush Subtree: Canceling build.';
      }
    }

    // Instantiate new commander to generate subtree commands.
    $subtree = new SubtreeCommander($subtree_name, $details);

    // Collect commands as $subtree_commands, then add them all to the
    // beguinning of $commands->prebuild array.
    // It's important these run before drush make for
    // two reasons: (1) Incase a project's build file includes a make file in a
    // subtree project. This will ensure the updated make file is included in
    // the build. (2) This needs to run before anything else dirties the working
    // tree (like drush make), otherwise the subtree add/pull/merge will fail.
    // First, add git subtree if it doesn't already exist.
    if ($subtree_add = $subtree->add(TRUE)) {
      drush_log(dt('Preparing to add subtree: !subtree_name',
             array('!subtree_name' => $subtree_name)), 'ok');
      $subtree_commands[] = $subtree_add;
    }
    // Otherwise, pull in any updates.
    elseif ($subtree_pull = $subtree->pull()) {
      $subtree_commands[] = $subtree_pull;
    }

    // Use git subtree merge to check out a particular version of a project.
    if ($id) {
      $subtree_commands[] = $subtree->merge($id, $tag);
    }
    else {
      // @todo Detect latest recommended release on d.o when no version is
      // specified. Consider using that to better match standard make file
      // behavior?
      drush_log(dt("No commit ID specified for !project (if a tag was specified in a make file, the corresponding commit ID could not be retrieved). Your install will run on the tip of whatever branch you checked out. (Subtrees do not fallback to the latest recommended release on drupal.org when no version is specified.)", array('!project' => $subtree_name)), 'warning');
    }

    // End loop thorugh subtrees.
  }

  // Add symlink commands after drush make but before other commands, incase any
  // custom post-build commands are committing anything. This way, git history
  // doesn't get polluted with projects being re-added and re-removed each time.
  $commands->postbuild = array_merge($symlink_commands, $commands->postbuild);

  // Now add all subtree_commands to begining of prebuild command list.
  $commands->prebuild = array_merge($subtree_commands, $commands->prebuild);

  // No return necessary. Commands added to $command object are available to
  // buildmaster_build command now. Note: Returning anything actually triggers
  // Build Manger abort.
}

/**
 * Run helpful checks for developers during hook_buildmanager_build().
 *
 * Look for indications that projects may not been synced properly. Then prompt
 * developer with information about what we found and tips on resolving the
 * situation.
 *
 * @param string $name
 * @param string $tag
 * @param string $id
 * @param string $details
 */
function _drushsubtree_dev_checks($name, $tag, $id, $details) {
  // Assume we're proceeding with build unless checks prove otherwise.
  $proceed_with_build = TRUE;

  // Set vars for subtree check prompts.
  $check_vars = array(
    '@name' => $name,
    '@tag' => $tag,
    '@id' => $id,
    '@uri' => $details['uri'],
    '@branch' => $details['branch'],
  );

  // There's a tagged version of this project specified in the make file.
  if ($tag) {
    // Does local copy of subtree project match the version in the make file?
    // If yes, proceed. If no, prompt user with warnings and suggestions.
    // @TODO Do validation check.
    $message = dt("Your local copy of @name does not match @tag (specified in your make file). If you intend to pull in updates from outside your site repo with @tag, proceed. If your local version is ahead of @tag and you have been doing development inside your site repo, you should probably stop, push changes to @uri, tag a new version, update your make file, then rebuild. Otherwise, proceeding will be like downgrading to @tag. Do you want to proceed with this build? (To rebuild without interrupting local development on subtree projects, cancel and re-try with the --no-subtree-updates flag.)", $check_vars);
    $proceed_with_build = drush_confirm($message);
  }
  // There's no tagged version specified in the make file, but a commit ID is
  // specified.
  elseif ($id && !$tag) {
    // @todo
    $message = dt("Your local copy of @name does not match @id (specified in your make file). If you intend to pull in updates from outside your site repo with @id, proceed. If your local version is ahead of @id and you have been doing development inside your site repo, you should probably stop, push changes to @uri, update your make file, then rebuild. Otherwise, proceeding will be like downgrading to @id. Do you want to proceed with this build? (To rebuild without interrupting local development on subtree projects, cancel and re-try with the --no-subtree-updates flag.)", $check_vars);
    $proceed_with_build = drush_confirm($message);
  }
  // There's no tagged version for this project in the make file.
  elseif (!$id && !$tag) {
    // Do local and remote HEAD point at same commit? If yes, proceed. If no,
    // prompt user with warnings and suggestions.
    $message = dt("The version of @name in your local site repo does not match HEAD on @branch (@uri). Do you want to proceed with this build? (To rebuild without interrupting local development on subtree projects, cancel and re-try with the --no-subtree-updates flag.)", $check_vars);
    $proceed_with_build = drush_confirm($message);
  }

  return $proceed_with_build;
}

/**
 * Prep projects directory.
 */
function _drushsubtree_prep_projects_directory() {
  // Before adding/pulling subtrees, make sure parent directory
  // for --prefix exists.
  if (!file_exists('projects')) {
    $success = mkdir('projects', 0777, TRUE);
    if (!$success) {
      return drush_set_error('buildmanager', dt("Failed creating directory: projects"), 'error');
    }
  }
  elseif (file_exists('projects') && !is_dir('projects')) {
    return drush_set_error('buildmanager', dt("Please remove the 'projects' file. We need to create a directory with that name for your subtrees."), 'error');
  }

  if ($success) {
    drush_log(dt('A projects directory has been created at the top of your git repo. Git subtrees will be added there.'), 'ok');
  }
}

/**
 * Implements hook_buildmanager_build_options().
 */
function drushsubtree_buildmanager_build_options() {
  return array(
    'no-subtree-updates' => array(
      'description' => 'Do add/pull/merge subtrees in buildmanager config.',
    ),
    'subtree-dev-checks' => array(
      'description' => "Recommended for developers doing a rebuild after making changes to included contrib projects. Drush Subtree will run checks like: comparing included subtree projects with corresponding the versions in your make file, comparing local and remote HEAD. If things are out of sync, you will be notified, given suggestions about steps to take, and receive a prompt to optionally cancel the build.",
    ),
  );
}

/**
 * Implements hook_buildmanager_configure().
 *
 * Prompt for subtree info to be included in buildmanager config.
 * Returns config with subtree properties added, to be included in
 * buildmanager.config.yml.
 *
 * param array $config
 *   See hook_buildmanager_configure.
 *
 * pararm bool $prompt
 *   Ask user if project includes subtrees.
 */
function drushsubtree_buildmanager_configure($config, $prompt = TRUE) {
  if ($prompt && drush_confirm("\n" . dt("Does your build include subtrees?")) == FALSE) {
    // Our work here is done. Return unmodified $config array.
    return $config;
  }
  else {
    drush_print("\n" . dt("I'll help you set up configuration for subtrees. Later when Build Manager prompts you for info about symlinks, don't worry about your subtrees. Drush Subtree will take care of setting up and restoring those symlinks for you when Build Manager (re)builds."));
  }

  drush_print("\n" . dt("subtree properties..."));
  drush_print(dt("Tell me about any subtrees included in this build one-by-one."));
  $subtrees = array();
  $get_subtrees = TRUE;
  // Get subtree properties.
  while ($get_subtrees) {
    $name = drush_prompt(dt("What's the name of your subtree"));

    drush_print(dt("Please enter the path to the project in your codebase (e.g. docroot/sites/all/modules/custom/my-project)"));
    $subtrees[$name]['path'] = drush_prompt("path");

    drush_print(dt("Repo URI"));
    $subtrees[$name]['uri'] = drush_prompt("uri");

    drush_print(dt("Branch to pull from and push to"));
    $subtrees[$name]['branch'] = drush_prompt(dt("branch"));

    drush_print(dt("(Optional) Add a standard commit message to be included in any subtree add/pull/merge commits."));
    $default_message = "{$name} subtree from {$subtrees[$name]['uri']}";
    $subtrees[$name]['message'] = drush_prompt(dt("message"), $default_message);

    // Continue collecting info about more subtrees?
    $get_subtrees = drush_confirm(dt("Does your build include any more subtrees?"));
  }

  // Show subtree properties to user. Confirm they're right.
  // Show commands to user. Confirm they're right.
  drush_print("\n" . dt("Here are the subtree properties you entered:" . "\n"));
  drush_print(drush_format($subtrees, NULL, 'yaml'));
  if (!drush_confirm("Are these properties correct?")) {
    // Do over.
    $subtrees = drushsubtree_buildmanager_configure($config);
  }

  // Set subtrees property in Build Manager config file.
  $config['subtrees'] = $subtrees;
  return $config;
}

/**
 * Callback for drushsubtree-add (subtree-add).
 *
 * @param string $name
 *   Name of subtree.
 */
function drush_drushsubtree_subtree_add($name = '') {
  // Get buildmanager config.
  $config = _drushsubtree_get_config();

  // Get name if not passed as argument.
  if (!$name) {
    $name = _drushsubtree_get_name($config);
  }
  // Otherwise, confirm name passed is valid.
  elseif (!isset($config['subtrees'][$name])) {
    return drush_set_error(dt('Sorry. No properties for a subtree with this name could be found in your config file: !name',
        array('!name' => $name)));
  }

  // Generate subtree add command and execute it.
  $properties = $config['subtrees'][$name];
  $subtree = new SubtreeCommander($name, $properties);
  if ($subtree_add = $subtree->add()) {
    _drushsubtree_shell_exec($subtree_add);
  }
}

/**
 * Find, parse, return buildmanager config.
 *
 * @return array
 *   Parsed buildmanager.config.yml.
 */
function _drushsubtree_get_config() {
  if (!function_exists('buildmanager_get_config_file')) {
    return drush_set_error('drushsubtree', dt('Missing Drush dependency: Build Manager'));
  }

  // First check for --config_file=path/to/buildmanager.config.yml flag.
  if (!$config_file = drush_get_option('config_file', '')) {
    // If not specified, buildmanager will check for a config file or prompt for
    // selection if many are found in top-level directory of repo.
    $config_file = buildmanager_get_config_file();
  }
  // Now parse config file.
  $config = buildmanager_get_config($config_file);

  return $config;
}

/**
 * Callback for drush drushsubtree-checkout (subtree-checkout).
 *
 * Faux subtree command. Works like `git checkout <id>` or `git checkout <tag>`.
 *
 * @param string $name
 *   Subtree name.
 *
 * @param string $ref
 *   Git commit ID or tag.
 */
function drush_drushsubtree_subtree_checkout($name, $ref) {
  // Get buildmanager config.
  $config = _drushsubtree_get_config();

  // Make sure there are subtrees in config.
  if (!isset($config['subtrees'])) {
    return drush_set_error(dt('No subtrees found in buildmanager config file.'));
  }
  // Make sure named subtree is there.
  elseif (!isset($config['subtrees'][$name])) {
    return drush_set_error(
      dt('No subtree with this name found in buildmanager config file: !name',
      array('!name' => $name))
    );
  }
  else {
    // Grab project properties from config.
    $properties = $config['subtrees'][$name];
  }

  // Determine if $ref is a tag or a commit ID. (This check is pretty
  // unsophistocated. If $ref is 40 characters, assume it's a commit ID,
  // otherwise it's a tag.) Then get/set $id so we can do a subtree merge to
  // "checkout" the desired tag/id.
  (strlen($ref) == 40) ? $id = $ref : $tag = $ref;
  if ($tag) {
    // It's not 40 characters (not a SHA1), assume $ref is a tag.
    $project_info = buildmanager_get_project_info($name, $config);
    $id = _drushsubtree_get_project_id($name, $project_info, $properties, $ref);
  }

  drush_print(dt('Note: "checkout" is not a real subtree command. This is really just a friendly wrapper around subtree merge.'), 'notice');

  $subtree = new SubtreeCommander($name, $properties);
  _drushsubtree_shell_exec($subtree->merge($id, $tag));
}

/**
 * Callback for drushsubtree-pull (subtree-pull).
 *
 * @param string $name
 *   Name of subtree.
 */
function drush_drushsubtree_subtree_pull($name = '') {
  // Get buildmanager config.
  $config = _drushsubtree_get_config();

  // Get name if not passed as argument.
  if (!$name) {
    $name = _drushsubtree_get_name($config);
  }

  $properties = $config['subtrees'][$name];
  $subtree = new SubtreeCommander($name, $properties);
  _drushsubtree_shell_exec($subtree->pull());
}

/**
 * Callback for drushsubtree-merge (subtree-merge).
 *
 * @param string $name
 *   Optional name of subtree to merge.
 *
 * @param string $id
 *   Optional commit id to merge to.
 */
function drush_drushsubtree_subtree_merge($name = '', $id = '') {
  // Get buildmanager config.
  $config = _drushsubtree_get_config();

  // Get name if not passed as argument.
  if (!$name) {
    $name = _drushsubtree_get_name($config);
  }

  // Get project info from make file(s).
  $project_info = buildmanager_get_project_info($name, $config);

  // Get git tag and id.
  $properties = $config['subtrees'][$name];
  if (!$id) {
    $core = buildmanager_get_core_version($config);
    $tag = _drushsubtree_get_project_tag($name, $project_info, $core);
    $id = _drushsubtree_get_project_id($name, $project_info, $properties, $tag);
  }

  $subtree = new SubtreeCommander($name, $properties);
  _drushsubtree_shell_exec($subtree->merge($id, $tag));
}

/**
 * Callback for drushsubtree-push (subtree-push).
 *
 * @param string $name
 *   Name of subtree.
 */
function drush_drushsubtree_subtree_push($name) {
  // Get buildmanager config.
  $config = _drushsubtree_get_config();

  // Get name if not passed as argument.
  if (!$name) {
    $name = _drushsubtree_get_name($config);
  }

  if (!$properties = $config['subtrees'][$subtree_name]) {
    return drush_set_error(dt('No subtree config available for !subtree in !config_file'),
      array('!subtree' => $subtree_name, '!config_file' => $config_file));
  }

  $properties = $config['subtrees'][$name];
  $subtree = new SubtreeCommander($name, $properties);
  _drushsubtree_shell_exec($subtree->push());
}

/**
 * Prompt user to select subtree from options in config file.
 *
 * TODO If only one, use that, no prompt. Notify user decision has been made.
 *
 * @param array $config
 *   Parsed config from buildmanager config file.
 *
 * @return string
 *   Name of subtree
 */
function _drushsubtree_get_name($config) {
  $names = array_keys($config['subtrees']);
  $names = array_combine($names, $names);
  $name = drush_choice($names, dt('Select a subtree project:'));
  return $name;
}

/**
 * Callback for drushsubtree (subtree) command.
 *
 *     drush subtree <command> <name> [<args>,...]
 */
function drush_drushsubtree_subtree() {
  // Get $args and build array to pass to subtree command.
  $args = func_get_args();
  if (!$args) {
    // When no args are passed, return help (like `git subtree`).
    $command = 'drush subtree --help';
    $output = shell_exec($command);
    drush_print($output);
    return;
  }

  // Remove $command (arg0).
  $command = array_shift($args);

  // Name of function to call for desired drushsubtree command.
  $function = 'drush_drushsubtree_subtree_' . $command;

  // Call drush subtree <command> [<args>,...].
  call_user_func_array($function, $args);
}

/**
 * Wrapper around drush_shell_exec for standard error reporting.
 *
 * @param string $command
 *   Command to be executed.
 *
 * @return bool
 *   Succes/fail based on drush_shell_exec result.
 */
function _drushsubtree_shell_exec($command) {
  $success = drush_shell_exec($command);
  if (!$success) {
    // Command failed. Notify user and exit.
    drush_log(dt('Command failed: !command', array('!command' => $command)), 'error');
    $output = drush_shell_exec_output();
    drush_log(implode("\n", $output), 'error');
    $error_message = drushsubtree_parse_error_output($output);
    return drush_set_error($error_message);
  }
  return $success;
}

/**
 * Implements hook_buildmanager_parse_error_output().
 */
function drushsubtree_buildmanager_parse_error_output($output) {
  if ($message = drushsubtree_parse_error_output($output, FALSE)) {
    drush_log($message, 'error');
  }
}

/**
 * Parse exec() $output for known problems. Provide helpul tips.
 *
 * @param array $output
 *   Output, line by line, returned by exec().
 *
 * @param bool $return_generic
 *   Return a generic message if no specific insight is available.
 *
 * @return string
 *   Helpful error message. Tip, if available.
 */
function drushsubtree_parse_error_output($output, $return_generic = TRUE) {
  $message = '';

  foreach ($output as $line) {
    $message .= drushsubtree_parse_error_line($line);
  }

  if (!$message && $return_generic) {
    // No special helpful message is available.
    $message = dt('Review git-subtree error message above to see why your drush subtree command failed.');
  }

  return $message;
}

/**
 * Parse a line of error output for known problems. Provide helpul tips.
 *
 * @param string $line
 *   Individual line of $output. @see drushsubtree_parse_error_output.
 *
 * @return string
 *   Translated string to be appended to error message for user.
 */
function drushsubtree_parse_error_line($line) {
  $message = '';

  // An error message like this indicates that the directory ("prefix") being
  // pulled into is not a subtree:
  // "Can't squash-merge: 'projects/my-project' was never added."
  $beginning = substr($line, 0, 19);
  $ending = substr($line, -16);
  if ($beginning == "Can't squash-merge:" && $ending == "was never added.") {
    $prefix = substr($line, 21, -18);
    $project = substr($line, strrpos($line, '/') + 1, -18);
    $message = dt("There are files here, !here, but they were not added to the repo with `drush subtree add` or `git subtree add`. To fix: !fix",
      array('!here' => $prefix, '!fix' => "\n\tgit rm -r {$prefix};\n\tgit commit -m 'Remove files to be re-added with subtree add.';\n\tdrush subtree add {$project};")
    );
  }

  // @todo Add more checks for common errors here...

  return $message;
}

/**
 * Callback for subtree-get-subtrees.
 */
function drush_drushsubtree_subtree_get_subtrees() {
  $config = _drushsubtree_get_config();
  foreach ($config['subtrees'] as $name => $details) {
    drush_print($name);
  }
}

/**
 * Callback for subtree-get-info.
 */
function drush_drushsubtree_subtree_get_info($name = '') {
  // Get buildmanager config.
  $config = _drushsubtree_get_config();

  // Get name if not passed as argument.
  if (!$name) {
    $name = _drushsubtree_get_name($config);
  }
  // Otherwise, confirm name passed is valid.
  elseif (!isset($config['subtrees'][$name])) {
    return drush_set_error(dt('Sorry. No properties for a subtree with this name could be found in your config file: !name',
        array('!name' => $name)));
  }

  $info[$name] = $config['subtrees'][$name];
  drush_print("\n" . drush_format($info, NULL, 'yaml'));
}

/**
 * Callback for subtree-compare-heads.
 */
function drush_drushsubtree_subtree_compare_heads($name = '') {
  // Get buildmanager config.
  $config = _drushsubtree_get_config();

  // Get name if not passed as argument.
  if (!$name) {
    $name = _drushsubtree_get_name($config);
  }

  if (!$properties = $config['subtrees'][$name]) {
    return drush_set_error(dt('No subtree config available for !subtree in !config_file'),
      array('!subtree' => $name, '!config_file' => $config_file));
  }

  if (drushsubtree_heads_match($name, $properties, TRUE)) {
    drush_print(dt("Local and remote versions of @name match.", array('@name' => $name)));
  }
  else {
    drush_print(dt("Local and remote versions of @name do NOT match.", array('@name' => $name)));
  }
}

/**
 * Compare heads and return true/false for match.
 *
 * @param string $name
 *   Project name.
 *
 * @param array $properties
 *   Project details from buildmanager config.
 *
 * @param bool $log
 *   Log details about comparison.
 *
 * @return bool
 *   TRUE, match. FALSE, not matching.
 */
function drushsubtree_heads_match($name, $properties, $log = FALSE) {
  $local_head = drushsubtree_subtree_get_head($name, $properties);
  $remote_head = drushsubtree_get_remote_head($properties['uri'], $properties['branch']);

  if ($log) {
    drush_log("{$name}\tlocal HEAD\t{$local_head}", 'ok');
    drush_log("{$name}\tremote HEAD\t{$remote_head}", 'ok');
  }

  return ($local_head == $remote_head) ? TRUE : FALSE;
}

/**
 * Callback for subtree-compare-tag.
 */
function drush_drushsubtree_subtree_compare_tag($name = '') {
  // Get buildmanager config.
  $config = _drushsubtree_get_config();

  // Get name if not passed as argument.
  if (!$name) {
    $name = _drushsubtree_get_name($config);
  }

  if (!$details = $config['subtrees'][$name]) {
    return drush_set_error(dt('No subtree config available for !subtree in !config_file'),
      array('!subtree' => $name, '!config_file' => $config_file));
  }

  if (drushsubtree_compare_tag($name, $config, TRUE)) {
    drush_log(dt('Versions match'), 'ok');
  }
  else {
    drush_log(dt('Versions do not match'), 'warning');
  }
}

/**
 * Compare local subtree to tagged version specified by make file.
 *
 * @param string $name
 *   Project name.
 *
 * @param array $config
 *   Buildmanager config.
 *
 * @param bool $log
 *   Log details about comparison.
 *
 * @return bool
 *   TRUE, match. FALSE, not matching.
 */
function drushsubtree_compare_tag($name, $config, $log = FALSE) {
  // Assume false until we prove true.
  $result = FALSE;

  // Get project info from available make file(s).
  // Note: This function only has access to make files known to build.make. Make
  // files added and discovered at runtime are not taken into consideration
  // here.
  $project_info = buildmanager_get_project_info($name, $config);
  $core = buildmanager_get_core_version($config);
  $make_tag = _drushsubtree_get_project_tag($name, $project_info, $core);
  $build_file = $config['build']['build_file'];

  // Get local commit ID and corresponding tag from remote, if one exists.
  $details = $config['subtrees'][$name];
  $id = drushsubtree_subtree_get_head($name, $details);
  $project_tag = _drushsubtree_match_tag($name, $id, $details);

  if ($log) {
    $not_found = dt("No Tag Found");
    $project_tag = ($project_tag) ? $project_tag : $not_found;
    $make_tag = ($make_tag) ? $make_tag : $not_found;
    drush_log(dt("@project_tag:\tlocal version of @name, @id", array(
      '@project_tag' => $project_tag,
      '@name' => $name,
      '@id' => $id)), 'ok');
    drush_log(dt("@make_tag:\t@build_file version of @name", array(
      '@make_tag' => $make_tag,
      '@build_file' => $build_file,
      '@name' => $name)), 'ok');
  }

  // Compare tags.
  if ($make_tag == $project_tag && $make_tag != dt('Not Found')) {
    $result = TRUE;
  }

  return $result;
}
