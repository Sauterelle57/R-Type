# Contributing to RType project

Welcome to the contributing guide for the awesome project!

## Commit Message Conventions

We follow a specific convention for our commit messages to keep our Git history organized. Please use the following format:

- **Fix:**
  ```markdown
  fix (fix/branch-name): fix message content
  ```
- **Add:**
  ```markdown
  add (add/branch-name): add message content
  ```
- **Delete:**
  ```markdown
  delete (delete/branch-name): delete message content
  ```
For the branch name, create branches starting with fix/, add/, or delete/. When merging these branches, merge them into the dev branch, and then merge the dev branch into main.

## Example Workflow

- **Create a Fix branch:**
  ```markdown
  git checkout -b fix/bug-fix-description
- **Commit Changes:**
  ```markdown
  git commit -m "fix (fix/bug-fix-description): fix the issue"
- **Push Changes:**
  ```markdown
  git push origin fix/bug-fix-description
## Open a pull request

Create a pull request and target the dev branch.

## Merge to main

After your pull requests are approved, merge the dev branch into main.

# Creating a release

We use a script to automate the release process. Ensure you have GitHub CLI installed. If not, follow the installation instructions below.

- **At the root of the repository:**
  ```markdown
  ./create_release.sh -v "1.0.0"
Make sure to replace "1.0.0" with your desired version.

# Installing GitHub CLI

1. Download the GitHub CLI Package:
```markdown
  sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-key C99B11DEB97541F0
  sudo apt-add-repository https://cli.github.com/packages
  sudo apt update
```

2. Install GitHub CLI:
```markdown
sudo apt install gh
```
3. Verify the Installation:
```markdown
gh --version
```

4. Authenticate with GitHub:

Before using gh, you need to authenticate with your GitHub account:
```markdown
gh auth login
```
Follow the prompts to complete the authentication.
