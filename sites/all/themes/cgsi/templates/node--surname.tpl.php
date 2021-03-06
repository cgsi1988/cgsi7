<?php
/**
 * @file node.tpl.php
 *
 * Theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: Node body or teaser depending on $teaser flag.
 * - $picture: The authors picture of the node output from
 *   theme_user_picture().
 * - $date: Formatted creation date (use $created to reformat with
 *   format_date()).
 * - $links: Themed links like "Read more", "Add new comment", etc. output
 *   from theme_links().
 * - $name: Themed username of node author output from theme_user().
 * - $node_url: Direct url of the current node.
 * - $terms: the themed list of taxonomy term links output from theme_links().
 * - $submitted: themed submission information output from
 *   theme_node_submitted().
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type, i.e. story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $teaser: Flag for the teaser state.
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 */
?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"><div class="node-inner">

  <?php if (!$page): ?>
    <h2 class="title">
      <a href="<?php print $node_url; ?>" title="<?php print $title ?>"><?php print $title; ?></a>
    </h2>
  <?php endif; ?>

  <?php if ($unpublished): ?>
    <div class="unpublished"><?php print t('Unpublished'); ?></div>
  <?php endif; ?>

  <div class="meta">
    <?php print t('Last modified: @date', array('@date' => format_date($node->changed, 'custom', 'm/d/Y'))); ?>
  </div>

  <div class="content">
    
    <?php if ($page): ?>
      <p class="referer-links"><?php // print $referer_link; ?><a href="<?php print url('members/church-records/search/popup'); ?>" onclick="history.go(-1); return  false">Back to search results</a></p>
    <?php endif; ?>

    <p>
      <?php print t('<strong>Surname:</strong> @name<br/>', array('@name' => $node->title)); ?>
      <?php print t('<strong>City/Village of Origin:</strong> @city<br/>', array('@city' => $field_surname_european_city[0]['value'])); ?>
      <?php print t('<strong>European Country:</strong> @country<br/>', array('@country' => $field_surname_european_country[0]['value'])); ?>
      <?php print t('<strong>Immigration area (US or other):</strong> @area<br/>', array('@area' => $field_surname_immigration_area[0]['value'])); ?>
    </p>

    <?php print $field_surname_comments[0]['value']; ?>

    <p>
      <?php print t('<strong>Member submitting this surname:</strong> @first @last<br/>', array('@first' => $author->profile_first_name, '@last' => $author->profile_last_name)); ?>
      <?php print l(t('View all surname records submitted by this member'), 'members/surnames/search/user/' . $node->uid); ?><br/>
      <?php if ($author->mail): ?>
        <?php print t("<strong>Member's e-mail address:</strong> !link", array('!link' => l(check_plain($author->mail), 'mailto:' . $author->mail))); ?>
      <?php endif; ?>
    </p>
    <?php if (isset($author_mailing_address)): ?>
      <p><strong>Mailing address:</strong><br/>
      <?php print $author_mailing_address; ?>
      </p>
    <?php endif; ?>
    <p><?php print $author_status; ?></p>
  </div>

  <?php print $links; ?>

</div></div> <!-- /node-inner, /node -->
