> [!CAUTION]
> This package is in early development and should not be used in production.

# Rhythm Game Utilities

[![Tests](https://github.com/neogeek/rhythm-game-utilities/actions/workflows/test.workflow.yml/badge.svg)](https://github.com/neogeek/rhythm-game-utilities/actions/workflows/test.workflow.yml)
[![Build](https://github.com/neogeek/rhythm-game-utilities/actions/workflows/build.workflow.yml/badge.svg)](https://github.com/neogeek/rhythm-game-utilities/actions/workflows/build.workflow.yml)
[![Join the chat at https://discord.gg/nNtFsfd](https://img.shields.io/badge/discord-join%20chat-7289DA.svg)](https://discord.gg/nNtFsfd)

This library is a collection of utilities for creating rhythm games like Tap Tap Revenge, Guitar Hero, and Rock Band. It is meant to be used within any game engine that supports loading C++ libraries, such as Unity, Unreal, Godot and SDL.

![](screenshot.png)
_Prototype game built using these utilities._

## Features

- 🎵 Parse `.chart` and `.midi` song files
- 🎼 Calculate position to render notes
- 💯 Calculate hit accuracy
- 🥁 Determine if the current time is on the beat
- 💫 And more!

## Social

- Star [this repo on GitHub](https://github.com/neogeek/rhythm-game-utilities) for updates
- Follow me on [Bluesky](https://bsky.app/profile/scottdoxey.com) or [Twitter](https://twitter.com/neogeek)
- Join the [Discord](https://discord.gg/nNtFsfd)
- Follow me on [GitHub](https://github.com/neogeek/)

## Table of Contents

- [Platforms](#platforms)
- [Install](#install)
- [API](#api)

  1. [Audio](#audio)
     1. [ConvertSamplesToWaveform](#audioconvertsamplestowaveform)
  1. [Common](#common)
     1. [InverseLerp](#commoninverselerp)
     1. [Lerp](#commonlerp)
  1. [Parsers](#parsers)
     1. [ParseBpmFromChartSection](#parsersparsebpmfromchartsection)
     1. [ParseLyricsFromChartSection](#parsersparselyricsfromchartsection)
     1. [ParseMetaDataFromChartSection](#parsersparsemetadatafromchartsection)
     1. [ParseNotesFromChartSection](#parsersparsenotesfromchartsection)
     1. [ParseSectionsFromChart](#parsersparsesectionsfromchart)
     1. [ParseTimeSignaturesFromChartSection](#parsersparsetimesignaturesfromchartsection)
  1. [Utilities](#utilities)
     1. [CalculateAccuracyRatio](#utilitiescalculateaccuracyratio)
     1. [CalculateBeatBars](#utilitiescalculatebeatbars)
     1. [ConvertSecondsToTicks](#utilitiesconvertsecondstoticks)
     1. [ConvertTickToPosition](#utilitiesconvertticktoposition)
     1. [IsOnTheBeat](#utilitiesisonthebeat)
     1. [RoundUpToTheNearestMultiplier](#utilitiesrounduptothenearestmultiplier)

- [Architecture](#architecture)
- [Git Hooks](#git-hooks)
- [Testing](#testing)
- [Build](#build)
- [Contributing](#contributing)
- [Community Roadmap](#community-roadmap)
- [Other Projects](#other-projects)
- [License](#license)
