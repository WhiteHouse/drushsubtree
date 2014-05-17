<?php
/**
 * @file
 */
require_once('drushsubtree.commander.class.inc');

/**
 * GitCommander class.
 */
class GitCommander extends Commander {
  private $uri;
  private $branch;

  /**
   * Construct basic commander object.
   *
   * @param array $options
   *   - uri, string
   *   - branch, string
   */
  public function __construct($options = array()) {
    $uri =    (isset($options['uri']))    ? $options['uri']    : '';
    $branch = (isset($options['branch'])) ? $options['branch'] : '';

    $this->setUri($uri);
    $this->setBranch($branch);
  }

  /** 
   * Provides command to list remote's tags.
   *
   * @param 
   */
  function list_remote_tags() {
     if (!$this->uri) {
       throw new Exception("GitCommander::list_remote_head requires uri info.");  
     }
     $this->command = "git ls-remote --tags {$this->uri}";
     return $this->command;
  }

  /** 
   * Provides command to get HEAD for specified remote branch.
   */
   function get_remote_head() {
     if (!$this->uri || !$this->branch) {
       throw new Exception("GitCommander::get_remote_head requires uri and branch info.");  
     }
     $this->command = "git ls-remote --heads {$this->uri} {$this->branch}"; 
     return $this->command;
   }

  /**
   * Getters and setters =================================
   */

  /**
   * @return string
   */
   function getUri() {
     return $this->uri; 
   }

  /**
   * @param string
   */
   function setUri($uri) {
     $this->uri = $uri;  
   }

  /**
   * @return string
   */
   function getBranch() {
     return $this->branch;
   }

  /**
   * @param string
   */
   function setBranch($branch) {
     $this->branch = $branch;
   }
}
