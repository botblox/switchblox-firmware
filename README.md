<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Thanks again! Now go create something AMAZING! :D
***
***
***
*** To avoid retyping too much info. Do a search and replace for the following:
*** github_username, repo_name, twitter_handle, email, project_title, project_description
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]


<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://www.botblox.io/">
    <img src="images/logo.png" alt="Logo" width="160" height="160">
  </a>

  <h3 align="center">BotBlox Firmware</h3>

  <p align="center">
    Firmware created by BotBlox to configure settings on our products
    <br />
    <a href="https://botblox.atlassian.net/wiki/spaces/HARDWARE/overview"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://botblox.atlassian.net/wiki/spaces/HARDWARE/overview">View Demo</a>
    ·
    <a href="https://github.com/botblox/botblox-manager-firmware/issues">Report Bug</a>
    ·
    <a href="https://github.com/botblox/botblox-manager-firmware/issues">Request Feature</a>
  </p>
</p>



<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary><h2 style="display: inline-block">Table of Contents</h2></summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgements">Acknowledgements</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

[![Product Name Screen Shot][product-screenshot]](https://secureservercdn.net/160.153.138.163/257.9dc.myftpupload.com/wp-content/uploads/2020/06/Rev_C_Task_1_front.png)

Welcome to BotBlox Firmware. We designed this firmware with a singular goal: to allow our community of customers and developers to manually configure custom settings on BotBlox products, such as the SwitchBlox, our flagship Etheret switch. Our customers have requested for a while now that they want to be able to program VLAN membership, Quality-of-service, Port mirroring, etc on our products. This Firmware forms a part of our answer, along with our containerized pyhton application. 


### Built With

* [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html)


<!-- GETTING STARTED -->
### Prerequisites

Download and instal [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) - I used version 1.5.0 so I politely suggest that you use this version too.


## Getting Started

To get a local copy up and running follow these simple steps.
1. `cd` to `/path/to/STM32CubeIDE/workspace_1.5.0` directory
```sh
    cd /path/to/STM32CubeIDE/workspace_1.5.0
```
2. Clone this repo in the directory 
```sh
   git clone https://github.com/botblox/botblox-manager-firmware.git
```
3. When you open `STM32CubeIDE` and choose `workspace_1.5.0`, you should see the project appear in the file directory within the application.

If this project does not appear - this can happen (though I'm not sure why):
1. Copy the `IP175G_PARSER_BUILD.ioc` to any directory at hand
2. In `STM32CubeIDE`, go to `File`->`New`->`STM32 Project from an Existing STM32CubeMX configuration file (.ioc)`
3. Select `/path/to/IP175G_PARSER_BUILD.ioc` and then `Finish`
4. You know can generate code for the project with the correct periphery and DMA configuration on the STM32L011D4 processor on the SwitchBlox. 
5. From the new project's directory, replace `Core/Inc/*` with `Core/Inc/*` in this repo.
6. Now replace `Core/Src/*` in the project directory with `Core/Src/*` from this repo.
7. You know have a local version (albeit a read-only version) on your machine which you can use. 


<!-- USAGE EXAMPLES -->
## Usage

Use this space to show useful examples of how a project can be used. Additional screenshots, code examples and demos work well in this space. You may also link to more resources.

_For more examples, please refer to the [Documentation](https://example.com)_


<!-- ROADMAP -->
## Roadmap

See the [open issues](https://github.com/botblox/botblox-manager-firmware/issues) for a list of proposed features (and known issues).


<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
2. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
3. Push to the Branch (`git push origin feature/AmazingFeature`)
4. Open a Pull Request

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.

<!-- CONTACT -->
## Contact

BotBlox email - [Contact here](mailto:josh@kapek.org)

Project Link: [https://github.com/botblox/botblox-manager-firmware](https://github.com/botblox/botblox-manager-firmware)


<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements

* []()
* []()
* []()


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors-anon/botblox/botblox-manager-firmware?style=for-the-badge
[contributors-url]: https://github.com/botblox/botblox-manager-firmware/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/botblox/botblox-manager-firmware?style=for-the-badge
[forks-url]: https://github.com/botblox/botblox-manager-firmware/network/members
[stars-shield]: https://img.shields.io/github/stars/botblox/botblox-manager-firmware?style=for-the-badge
[stars-url]: https://github.com/botblox/botblox-manager-firmware/stargazers
[issues-shield]: https://img.shields.io/github/issues/botblox/botblox-manager-firmware?style=for-the-badge
[issues-url]: https://github.com/botblox/botblox-manager-firmware/issues
[license-shield]: https://img.shields.io/github/license/botblox/botblox-manager-firmware?style=for-the-badge
[license-url]: https://github.com/botblox/botblox-manager-firmware/blob/main/LICENSE
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/company/botblox/

