	t.Run("will protect against zip slip exploit", func(t *testing.T) {
		tmpDir := createTmpDir(t)
		defer deleteTmpDir(t, tmpDir)

		// Create a malicious tar.gz archive in memory
		var buf bytes.Buffer
		gzw := gzip.NewWriter(&buf)
		tw := tar.NewWriter(gzw)

		// Add a malicious file entry that tries to escape the target directory
		maliciousPath := "../../../etc/passwd"
		hdr := &tar.Header{
			Name: maliciousPath,
			Mode: 0644,
			Size: int64(len("malicious content")),
		}
		if err := tw.WriteHeader(hdr); err != nil {
			t.Fatalf("Failed to write tar header: %v", err)
		}
		if _, err := tw.Write([]byte("malicious content")); err != nil {
			t.Fatalf("Failed to write tar content: %v", err)
		}

		// Close the tar and gzip writers
		if err := tw.Close(); err != nil {
			t.Fatalf("Failed to close tar writer: %v", err)
		}
		if err := gzw.Close(); err != nil {
			t.Fatalf("Failed to close gzip writer: %v", err)
		}

		err := files.Untgz(tmpDir, &buf, math.MaxInt64, false)
		assert.NoError(t, err)

		// Verify that the file was not created outside the temp directory
		targetPath := filepath.Join(tmpDir, maliciousPath)
		t.Logf(targetPath)
		if _, err := os.Stat(targetPath); err == nil {
			t.Fatalf("Malicious file was created: %s", targetPath)
		}
	})
